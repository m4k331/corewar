package pages

const (
	Main         = "Main page"
	NotFound     = "404 Not found page"
	Construction = "Construction page"
	NewGame      = "New game page"
	RandomGame   = "Random game page"
	LocalGame    = "Local game page"
	ListOfGame   = "List of game page"
)

var Pages = map[string]string{
	Main:         "templates/main.html",
	NotFound:     "templates/404.html",
	Construction: "templates/construction.html",
	NewGame:      "templates/new_game.html",
	RandomGame:   "templates/random_game.html",
	LocalGame:    "templates/local_game.html",
	ListOfGame:   "templates/list_of_game.html",
}
