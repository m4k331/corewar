package main

import (
	"go.uber.org/zap"
	"net"
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

func handleConnection(conn net.Conn, connLog *zap.Logger, handler func(net.Conn, *zap.Logger) error) {
	defer connClose(conn, connLog)
	defer connLog.Sync()

	for {
		if err := handler(conn, connLog); err != nil {
			connLog.Error("Abort connection",
				zap.String("addr", conn.RemoteAddr().String()),
				zap.Error(err),
			)
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
			genLog.Error("General socket accept failed",
				zap.Error(err),
			)
			continue
		}

		genLog.Info("Service connected to hub server",
			zap.String("addr", conn.RemoteAddr().String()),
		)

		connLog, err := zap.NewProduction()
		if err != nil {
			genLog.Error("Connection logger created failed",
				zap.Error(err),
			)
			connClose(conn, genLog)
			continue
		}

		go handleConnection(conn, connLog, handleGeneralSocket)
		// TODO: delete
		//go func() {
		//	timer := time.NewTimer(time.Second * 5)
		//	<-timer.C
		//	tmpInitialGame(conn, 1) // n - number champs
		//}()
	}
}
