package main

import (
	"fmt"
	"net"
	"strconv"
	"strings"
)

func readTypeMsg(conn net.Conn) (uint8, error) {
	oneByte := make([]byte, 1)
	n, err := conn.Read(oneByte)
	if n != 1 {
		err = fmt.Errorf("%d bytes were read instead of 1", n)
	}
	return oneByte[0], err
}

func portFromAddress(addr string) uint32 {
	port, _ := strconv.Atoi(addr[strings.LastIndex(addr, ":")+1:])
	return uint32(port)
}
