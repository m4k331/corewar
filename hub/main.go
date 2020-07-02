package main

import (
	"encoding/json"
	"fmt"
	"html/template"
	"log"
	"net/http"
	"strings"
)

var mainPage = []byte(`
<!DOCTYPE html>
<html>
<body>
  <a href="https://api.intra.42.fr/oauth/authorize?client_id=226c8da5a137547372b2017c4042fc069a0605b46bc69b78c313c20944fa6001&redirect_uri=http%3A%2F%2Flocalhost%3A4221%2Foauth&response_type=code">
    Login with 42
  </a>
</body>
</html>
`)

var clientID = `226c8da5a137547372b2017c4042fc069a0605b46bc69b78c313c20944fa6001`
var clientSecret = `f8728101814bf2864788cc6bddb09ce03ce28c2f810b69ee385cd6e34fad7e5e`

func root(w http.ResponseWriter, r *http.Request) {
	t := template.New("signin")
	t, err := t.ParseFiles("html/signin.html")
	if err != nil {
		log.Fatal(err)
	}
	t.ExecuteTemplate(w, "signin", nil)
	fmt.Printf("root: %+v\n", t)
}

func mmain(w http.ResponseWriter, r *http.Request) {
	t := template.New("main")
	t, err := t.ParseFiles("html/index.html")
	if err != nil {
		log.Fatal(err)
	}
	t.ExecuteTemplate(w, "main", nil)
	fmt.Printf("main: %+v\n", t)
}

type OAuthAccessResponse struct {
	AccessToken string `json:"access_token"`
	Type        string `json:"token_type"`
	Expires     int    `json:"expires_in"`
	Scope       string `json:"scope"`
	Create      int    `json:"created_at"`
}

type IntraUser struct {
	Id          int           `json:"id"`
	Email       string        `json:"email"`
	Login       string        `json:"login"`
	URL         string        `json:"url"`
	DisplayName string        `json:"displayname"`
	ImageURL    string        `json:"image_url"`
	Staff       bool          `json:"staff?"`
	Course      []IntraCourse `json:"cursus_users"`
	Campus      []IntraCampus `json:"campus"`
}

type IntraCourse struct {
	Id    int     `json:"id"`
	Grade string  `json:"grade"`
	Level float32 `json:"level"`
}

type IntraCampus struct {
	Id       int    `json:"id"`
	Name     string `json:"name"`
	TimeZone string `json:"time_zone"`
}

func oauth(w http.ResponseWriter, r *http.Request) {
	httpClient := http.Client{}
	err := r.ParseForm()
	if err != nil {
		fmt.Printf("Could not parse query: %v\n", err)
		w.WriteHeader(http.StatusBadRequest)
		return
	}
	code := r.FormValue("code")

	urii := `http%3A%2F%2Flocalhost%3A4221%2Foauth`
	reqURL := fmt.Sprintf("https://api.intra.42.fr/oauth/token?grant_type=authorization_code&client_id=%s&client_secret=%s&code=%s&redirect_uri=%s", clientID, clientSecret, code, urii)
	req, err := http.NewRequest(http.MethodPost, reqURL, nil)
	if err != nil {
		fmt.Printf("Could not create HTTP request: %v\n", err)
		w.WriteHeader(http.StatusBadRequest)
		return
	}
	req.Header.Set("accept", "application/json")

	res, err := httpClient.Do(req)
	if err != nil {
		fmt.Printf("Could not send HTTP request: %v", err)
		w.WriteHeader(http.StatusInternalServerError)
		return
	}
	defer res.Body.Close()

	var t OAuthAccessResponse
	if err := json.NewDecoder(res.Body).Decode(&t); err != nil {
		fmt.Printf("Could not parse JSON response: %v", err)
		w.WriteHeader(http.StatusBadRequest)
		return
	}

	meReq := "https://api.intra.42.fr/v2/me"
	header := strings.Title(t.Type) + " " + t.AccessToken

	req, err = http.NewRequest(http.MethodGet, meReq, nil)
	if err != nil {
		fmt.Printf("Could not create HTTP request: %v\n", err)
		w.WriteHeader(http.StatusBadRequest)
		return
	}
	req.Header.Set("Authorization", header)

	res, err = httpClient.Do(req)
	if err != nil {
		fmt.Printf("Could not send HTTP request: %v", err)
		w.WriteHeader(http.StatusInternalServerError)
		return
	}
	defer res.Body.Close()

	var user IntraUser
	if err := json.NewDecoder(res.Body).Decode(&user); err != nil {
		fmt.Printf("Could not parse JSON response: %v", err)
		w.WriteHeader(http.StatusBadRequest)
		return
	}

	fmt.Printf("OPS: %+v\n", user)
}

type Client struct {
	AccessToken string
}

func (cl *Client) ServeHTTP(w http.ResponseWriter, r *http.Request) {
	if r.Method == "GET" {
		sUrl := strings.Trim(r.URL.String(), "/")
		switch sUrl {
		case "", "signin":

		}
	}
}

func main() {
	var (
		client = new(Client)
	)

	http.ListenAndServe(":8081", client)
	//mainMux := http.NewServeMux()
	//mainMux.HandleFunc("/", root)
	//mainMux.HandleFunc("/oauth", oauth)
	//mainMux.HandleFunc("/main", mmain)
	//fmt.Println("Start server")
	//http.ListenAndServe(":4221", mainMux)
	//fmt.Println("Stop server")
}
