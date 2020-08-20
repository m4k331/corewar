package main

import (
	"go.uber.org/zap"
	"net"
	"strconv"
	"strings"
	"time"
)

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
