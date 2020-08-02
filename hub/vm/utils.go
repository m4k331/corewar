package main

import (
	"go.uber.org/zap"
	"net"
	"strconv"
	"strings"
	"time"
)

func ReadTypeMsg(conn *net.TCPConn) (uint8, error) {
	var (
		oneByte = make([]byte, 1)
		e       error
		n       int
	)
	for n == 0 {
		n, e = conn.Read(oneByte)
		if e != nil {
			break
		}
	}
	return oneByte[0], e
}

func ExtractPort(addr string) uint32 {
	port, _ := strconv.Atoi(addr[strings.LastIndex(addr, ":")+1:])
	return uint32(port)
}

func CloseFailedConnection(conn *net.TCPConn, log *zap.Logger, msg string, e error) error {
	if conn != nil {
		_ = conn.Close()
	}
	if log != nil {
		log.Error(msg, zap.Error(e))
	}
	return e
}

func GetTimeFromNSecond(n int) time.Time {
	t := time.Now()
	t.Add(time.Second * time.Duration(n))
	return t
}
