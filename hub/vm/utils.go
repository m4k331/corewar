package main

import (
	"net"
	"strconv"
	"strings"
)

func ReadTypeMsg(conn net.Conn) (uint8, error) {
	var (
		oneByte = make([]byte, 1)
		err     error
		n       int
	)
	for n == 0 {
		n, err = conn.Read(oneByte)
	}
	return oneByte[0], err
}

func ExtractPort(addr string) uint32 {
	port, _ := strconv.Atoi(addr[strings.LastIndex(addr, ":")+1:])
	return uint32(port)
}
