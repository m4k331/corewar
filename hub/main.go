package main

import (
	"encoding/json"
	"fmt"
	"net/http"
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
	w.Write(mainPage)
}

type OAuthAccessResponse struct {
	AccessToken string `json:"access_token"`
	Type string `json:"token_type"`
	Expires int `json:"expires_in"`
	Scope string `json:"scope"`
	Create int `json:"created_at"`
}

type User struct {
	Id int `json:"id"`
	Login string `json:"login"`
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

	fmt.Printf("{code:%s}\n", code)
	reqURL := fmt.Sprintf("https://api.intra.42.fr/oauth/token?grant_type=client_credentials&client_id=%s&client_secret=%s&code=%s", clientID, clientSecret, code)
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

	fmt.Printf("%+v\n", t)



	//req, err = http.NewRequest(http.MethodGet, "https://api.intra.42.fr/v2/me", nil)
	//if err != nil {
	//	fmt.Printf("Could not create HTTP request on v2/me: %v\n", err)
	//	w.WriteHeader(http.StatusBadRequest)
	//	return
	//}
	//req.Header.Set("accept", "application/json")
	//req.Header.Set("Authorization", fmt.Sprintf("%s %s", t.Type, t.AccessToken))
	//res, err = httpClient.Do(req)
	//if err != nil {
	//	fmt.Printf("Could not send HTTP request: %v", err)
	//	w.WriteHeader(http.StatusInternalServerError)
	//	return
	//}
	//defer res.Body.Close()
	//
	//fmt.Printf("%#v\n", res.Body)
	//var u User
	//if err := json.NewDecoder(res.Body).Decode(&u); err != nil {
	//	fmt.Printf("Could not parse JSON response: %v", err)
	//	w.WriteHeader(http.StatusBadRequest)
	//	return
	//}

	//fmt.Printf("%+v\n", u)
	//set cookie
	//w.Header().Set("Location", "/welcome.html?access_token="+t.AccessToken)
	//w.Write([]byte(t.AccessToken))
	//w.WriteHeader(http.StatusFound)
}

func main() {
	mainMux := http.NewServeMux()
	mainMux.HandleFunc("/", root)
	mainMux.HandleFunc("/oauth", oauth)
	fmt.Println("Start server")
	http.ListenAndServe(":4221", mainMux)
	fmt.Println("Stop server")
}
//{code:5abdfc3406941e2e06d4d1d27565c2678c95e8f1e7e575596bf0916c23759809}
//{AccessToken:a7f1e407dc91ae3bd4841bcf3dcdc57f3df6aec5230086c4adcf10d5093812d4}