package utils

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

func SafeChanClosure(ch interface{}) {
	loop := true
	switch ch.(type) {
	case chan interface{}:
		c := ch.(chan interface{})
		for loop {
			select {
			case _, ok := <-c:
				if !ok {
					loop = false
				}
			default:
				close(c)
				loop = false
			}
		}
	case chan struct{}:
		c := ch.(chan struct{})
		for loop {
			select {
			case _, ok := <-c:
				if !ok {
					loop = false
				}
			default:
				close(c)
				loop = false
			}
		}
	case chan int:
		c := ch.(chan int)
		for loop {
			select {
			case _, ok := <-c:
				if !ok {
					loop = false
				}
			default:
				close(c)
				loop = false
			}
		}
	case chan byte:
		c := ch.(chan byte)
		for loop {
			select {
			case _, ok := <-c:
				if !ok {
					loop = false
				}
			default:
				close(c)
				loop = false
			}
		}
	}
}
