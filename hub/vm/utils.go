package main

import (
	"go.uber.org/zap"
	"net"
	"strconv"
	"strings"
)

func connClose(conn net.Conn, logger *zap.Logger) {
	if err := conn.Close(); err != nil {
		logger.Error("Connection closed failed",
			zap.String("addr", conn.RemoteAddr().String()),
			zap.Error(err),
		)
		return
	}
	logger.Info("Connection closed",
		zap.String("addr", conn.RemoteAddr().String()),
	)
}

func readTypeMsg(conn net.Conn) (uint8, error) {
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

func portFromAddress(addr string) uint32 {
	port, _ := strconv.Atoi(addr[strings.LastIndex(addr, ":")+1:])
	return uint32(port)
}
