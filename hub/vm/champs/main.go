package main

import (
	"fmt"
	"os"
)

func main()  {
	f, _ := os.Open("ex.cor")
	b := make([]byte, 100000)
	n, _ := f.Read(b)
	fmt.Println(n)
}