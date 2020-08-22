package main

import (
	"bytes"
	"corewar/hub/gen"
	"corewar/hub/pages"
	"crypto/md5"
	"encoding/hex"
	"encoding/json"
	"html/template"
	"log"
	"math/rand"
	"net/http"
	"sort"
	"strconv"
	"strings"
	"sync"
	"time"
)

const (
	addr                  = ":8080"
	Mb                    = 1 << 20
	FailedRedirect        = "[Client: %s] Failed to redirect to %s: %v\n"
	FailedEncodeResponse  = "[Client: %s] Failed to encode response on url %s: %v\n"
	SuccessfullyRedirect  = "[Client: %s] Successfully to redirect to %s\n"
	SuccessfullyAddedGame = "[Client: %s] Successfully added new game %s\n"
	SuccessfullySendGames = "[Client: %s] Successfully send games %s\n"
	ErrorNumberBots       = "The number of bots must be 1..4"
	InvalidBot            = "Invalid bot %s"
)

type Game struct {
	Id      string
	Name    string
	Bots    map[string][]byte
	Total   int
	Created time.Time
	sync.RWMutex
}

type Games struct {
	g map[string]*Game
	sync.RWMutex
}

func NewGames() Games {
	return Games{g: make(map[string]*Game, 8)}
}

func (gs *Games) Set(g *Game) {
	gs.Lock()
	gs.g[g.Id] = g
	gs.Unlock()
}

func (gs *Games) Get(id string) *Game {
	gs.RLock()
	defer gs.RUnlock()
	return gs.g[id]
}

func (gs *Games) GetListOfGameTemplate() []*GameTemplate {
	gs.RLock()
	defer gs.RUnlock()
	list := make([]*GameTemplate, 0, len(gs.g))
	for k := range gs.g {
		list = append(list, gs.g[k].ConvertToTemplate())
	}
	sort.Slice(list, func(i, j int) bool {
		a, _ := strconv.Atoi(list[i].Id)
		b, _ := strconv.Atoi(list[j].Id)
		return a < b
	})
	return list
}

func (g *Game) Play() bool {
	g.RLock()
	defer g.RUnlock()
	return len(g.Bots) == g.Total
}

func (g *Game) ConvertToTemplate() *GameTemplate {
	g.RLock()
	defer g.RUnlock()
	tmpl := &GameTemplate{
		Id:      g.Id,
		Title:   g.Name,
		Bots:    make([]string, 0, len(g.Bots)),
		Current: len(g.Bots),
		Total:   g.Total,
		Play:    g.Play(),
	}
	for name := range g.Bots {
		tmpl.Bots = append(tmpl.Bots, name)
	}
	return tmpl
}

type GameTemplate struct {
	Id      string   `json:"id"`
	Title   string   `json:"title"`
	Bots    []string `json:"bots"`
	Current int      `json:"current"`
	Total   int      `json:"total"`
	Play    bool     `json:"play"`
}

type Base struct {
	Games     Games
	Bots      map[string][]byte
	Templates map[string]*template.Template
}

func NewBase(pages map[string]string) *Base {
	b := &Base{
		Games:     NewGames(),
		Bots:      make(map[string][]byte, 8),
		Templates: make(map[string]*template.Template, len(pages)),
	}
	for title, path := range pages {
		b.Templates[title] = template.Must(template.ParseFiles(path))
	}
	return b
}

func execTemplate(w http.ResponseWriter, r *http.Request, t *template.Template, d interface{}) {
	if e := t.Execute(w, d); e != nil {
		log.Printf(FailedRedirect, r.RemoteAddr, r.URL.String(), e)
		return
	}
	log.Printf(SuccessfullyRedirect, r.RemoteAddr, r.URL.String())
}

func (b *Base) MainPage(w http.ResponseWriter, r *http.Request) {
	execTemplate(w, r, b.Templates[pages.Main], nil)
}

func (b *Base) NotFoundPage(w http.ResponseWriter, r *http.Request) {
	execTemplate(w, r, b.Templates[pages.NotFound], nil)
}

func (b *Base) ConstructionPage(w http.ResponseWriter, r *http.Request) {
	execTemplate(w, r, b.Templates[pages.Construction], nil)
}

func (b *Base) NewGamePage(w http.ResponseWriter, r *http.Request) {
	execTemplate(w, r, b.Templates[pages.NewGame], nil)
}

func (b *Base) RandomGamePage(w http.ResponseWriter, r *http.Request) {
	execTemplate(w, r, b.Templates[pages.RandomGame], nil)
}

func (b *Base) LocalGamePage(w http.ResponseWriter, r *http.Request) {
	execTemplate(w, r, b.Templates[pages.LocalGame], nil)
}

func (b *Base) GamePage(w http.ResponseWriter, r *http.Request) {
	execTemplate(w, r, b.Templates[pages.Game], nil)
}

func (b *Base) ListOfGamePage(w http.ResponseWriter, r *http.Request) {
	execTemplate(w, r, b.Templates[pages.ListOfGame], &struct {
		Games []*GameTemplate
	}{
		b.Games.GetListOfGameTemplate(),
	})
}

type Bot struct {
	Name string `json:"name"`
	Code string `json:"code"`
}

func SendError(w http.ResponseWriter, r *http.Request, errMsg string) {
	log.Printf(FailedRedirect, r.RemoteAddr, r.URL.String(), errMsg)
	w.WriteHeader(http.StatusBadRequest)
	if e := json.NewEncoder(w).Encode(&struct {
		Error string `json:"error"`
	}{
		Error: errMsg,
	}); e != nil {
		log.Printf(FailedEncodeResponse, r.RemoteAddr, r.URL.String(), e)
	}
}

func GetMD5Hash(data []byte) string {
	hash := md5.Sum(data)
	return hex.EncodeToString(hash[:])
}

func (b *Base) CreateGame(w http.ResponseWriter, r *http.Request) {
	reqGame := &struct {
		Name  string `json:"name"`
		Bots  []Bot  `json:"bots"`
		Total int    `json:"total"`
	}{}
	if e := json.NewDecoder(r.Body).Decode(reqGame); e != nil {
		SendError(w, r, e.Error())
		return
	}
	if len(reqGame.Bots) < 1 && len(reqGame.Bots) > 4 {
		SendError(w, r, ErrorNumberBots)
		return
	}

	game := &Game{
		Name:  reqGame.Name,
		Bots:  make(map[string][]byte, reqGame.Total),
		Total: reqGame.Total,
	}
	for i := range reqGame.Bots {
		hash := GetMD5Hash([]byte(reqGame.Bots[i].Code))
		binBot, ok := b.Bots[hash]
		if !ok {
			//TODO: send to ASM
			// if invalid bot
			//   SendError(w, r, fmt.Sprintf(InvalidBot, reqGame.Bots[i].Name))
			//   return
		}
		// TODO: if received valid bot
		game.Bots[reqGame.Bots[i].Name] = binBot
		b.Bots[hash] = binBot
	}

	game.Id = gen.GetStringID()
	game.Created = time.Now()

	buff := new(bytes.Buffer)
	if e := json.NewEncoder(buff).Encode(&struct {
		Id string `json:"id"`
	}{
		Id: game.Id,
	}); e != nil {
		log.Printf(FailedEncodeResponse, r.RemoteAddr, r.URL.String(), e)
		return
	}
	b.Games.Set(game)
	w.WriteHeader(http.StatusOK)
	if _, e := buff.WriteTo(w); e != nil {
		log.Printf(FailedEncodeResponse, r.RemoteAddr, r.URL.String(), e)
		return
	}
	log.Printf(SuccessfullyAddedGame, r.RemoteAddr, game.Name)
}

func (b *Base) SendGames(w http.ResponseWriter, r *http.Request) {
	buff := new(bytes.Buffer)
	if e := json.NewEncoder(buff).Encode(&struct {
		Games []*GameTemplate `json:"games"`
	}{
		Games: b.Games.GetListOfGameTemplate(),
	}); e != nil {
		SendError(w, r, e.Error())
		return
	}
	w.WriteHeader(http.StatusOK)
	if _, e := buff.WriteTo(w); e != nil {
		log.Printf(FailedEncodeResponse, r.RemoteAddr, r.URL.String(), e)
		return
	}
	log.Printf(SuccessfullySendGames, r.RemoteAddr, r.URL.String())
}

func (b *Base) MockSendGames(w http.ResponseWriter, r *http.Request) {
	buff := new(bytes.Buffer)
	if e := json.NewEncoder(buff).Encode(&struct {
		Games []*GameTemplate `json:"games"`
	}{
		Games: []*GameTemplate{
			{
				Id:      "1",
				Title:   "First",
				Bots:    []string{"lotus"},
				Current: 1,
				Total:   1,
				Play:    true,
			},
			{
				Id:      "3",
				Title:   "THT",
				Bots:    []string{"ki", "sh", "ki"},
				Current: 3,
				Total:   3,
				Play:    true,
			},
			{
				Id:      "5",
				Title:   "14devochek",
				Bots:    []string{"ooo"},
				Current: 1,
				Total:   4,
				Play:    false,
			},
			{
				Id:      strconv.Itoa(rand.Intn(777) + 10),
				Title:   "RND",
				Bots:    []string{"bu"},
				Current: 1,
				Total:   rand.Intn(3) + 2,
				Play:    false,
			},
			{
				Id:      strconv.Itoa(rand.Intn(777) + 900),
				Title:   "RND #2",
				Bots:    []string{"bu"},
				Current: 1,
				Total:   rand.Intn(3) + 2,
				Play:    false,
			},
		},
	}); e != nil {
		SendError(w, r, e.Error())
		return
	}
	w.WriteHeader(http.StatusOK)
	if _, e := buff.WriteTo(w); e != nil {
		log.Printf(FailedEncodeResponse, r.RemoteAddr, r.URL.String(), e)
		return
	}
	log.Printf(SuccessfullySendGames, r.RemoteAddr, r.URL.String())
}

func (b *Base) ServeHTTP(w http.ResponseWriter, r *http.Request) {
	switch r.Method {
	case "GET":
		switch r.URL.String() {
		case "/":
			b.MainPage(w, r)
		case "/new_game":
			b.NewGamePage(w, r)
		case "/random_game":
			b.RandomGamePage(w, r)
		case "/local_game":
			b.LocalGamePage(w, r)
		case "/list_of_game":
			b.ListOfGamePage(w, r)
		case "/games":
			b.SendGames(w, r)
		case "/games-mock":
			b.MockSendGames(w, r)
		case "/profile", "/statistics", "/logout":
			b.ConstructionPage(w, r)
		default:
			if strings.HasPrefix(r.URL.String(), "/game/") {
				id := strings.TrimPrefix(r.URL.String(), "/game/")
				if game := b.Games.Get(id); game != nil {
					// TODO: process game
					b.GamePage(w, r)
					_ = game
					break
				}
			}
			b.NotFoundPage(w, r)
		}
	case "POST":
		switch r.URL.String() {
		case "/create_game":
			b.CreateGame(w, r)
		}
	}
}

// TODO: config
// TODO: server init
// TODO: wrap pages
func main() {
	base := NewBase(pages.Pages)

	mx := http.NewServeMux()
	mx.Handle("/", base)
	mx.Handle("/data/", http.StripPrefix(
		"/data/",
		http.FileServer(http.Dir("./data")),
	))
	mx.Handle("/game/data/", http.StripPrefix(
		"/game/data/",
		http.FileServer(http.Dir("./data")),
	))

	server := http.Server{
		Addr:           addr,
		Handler:        mx,
		ReadTimeout:    5 * time.Second,
		WriteTimeout:   5 * time.Second,
		MaxHeaderBytes: 1 * Mb,
	}

	log.Println("Start server")
	if err := server.ListenAndServe(); err != nil {
		panic(err)
	}
}
