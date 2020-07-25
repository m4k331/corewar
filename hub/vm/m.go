package main

import (
	"fmt"
	"os"
)

func main() {
	config, err := NewConfig(os.Args[1])
	if err != nil {
		panic(err)
	}
	fmt.Printf("%v\n", config)
}
