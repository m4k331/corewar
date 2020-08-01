package main

import (
	"go.uber.org/zap"
	"net"
	"strconv"
	"strings"
	"time"
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

func CloseErrorConnection(conn *net.TCPConn, logger *zap.Logger, msg string, err error) error {
	if conn != nil {
		_ = conn.Close()
	}
	logger.Error(msg, zap.Error(err))
	return err
}

func GetTimeFromNSecond(n int) time.Time {
	t := time.Now()
	t.Add(time.Second * time.Duration(n))
	return t
}
