package main

import "fmt"

const CP = "/home/ahugh/go/cw/hub/vm/config/config.yaml"

func main() {
	config, err := NewConfig(CP)
	if err != nil {
		panic(err)
	}
	fmt.Printf("%v\v", config)
}
