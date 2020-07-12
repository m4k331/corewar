package main

import (
	"fmt"
	"go.uber.org/zap"
	"net"
	"time"
)

const (
	GeneralPort = ":2142"
)

const (
	TypeMsgHandshakeVM = iota + 1
	_
	TypeMsgGameNotification
	TypeMsgGameStatus
	TypeMsgOperation
	TypeMsgStatusOfProcess
	TypeMsgEndOfGame
	TypeMsgGamePresentation
)

const (
	TypeMsgHandshakeHB = iota + 1
	TypeMsgInitialGame
	TypeMsgSendBot
)

const (
	TypeMsgHandshakeASM = iota + 101
	TypeMsgErrorASM
	TypeMsgBinaryASM
)

func handleConnection(conn net.Conn, handler func(net.Conn) error) {
	defer conn.Close()

	var (
		err  error
		addr = conn.RemoteAddr().String()
	)

	for {
		err = handler(conn)
		if err != nil {
			fmt.Printf("Abort conn: %s error: %v\n", addr, err)
			return
		}
	}
}

func main() {
	genLog, err := zap.NewProduction()
	if err != nil {
		panic(err)
	}
	defer genLog.Sync()

	general, err := net.Listen("tcp", GeneralPort)
	if err != nil {
		panic(err)
	}
	genLog.Info("Start hub server",
		zap.String("addr", general.Addr().String()),
	)

	for {
		conn, err := general.Accept()
		if err != nil {
			genLog.Info("General socket accept failed",
				zap.Error(err),
			)
		}
		genLog.Info("Service connected to hub server",
			zap.String("addr", conn.RemoteAddr().String()),
		)
		go handleConnection(conn, handleGeneralSocket)
		// TODO: delete
		go func() {
			timer := time.NewTimer(time.Second * 10)
			<-timer.C
			tmpInitialGame(conn, 3) // n - number champs
		}()
	}
}
