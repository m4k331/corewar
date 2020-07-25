package main

import (
	"go.uber.org/zap"
)

const (
	ConfigPath = "/home/ahugh/go/cw/hub/vm/config/config.yaml"
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

func main() {
	config, err := NewConfig(ConfigPath)
	if err != nil {
		panic(err)
	}

	hub, err := NewServiceManage(config)
	if err != nil {
		panic(err)
	}
	hub.Log.Info("Start hub server",
		zap.String("addr", hub.Addr),
	)

	for {
		service, err := hub.ConnectNewService()
		if err != nil {
			hub.Log.Error("Failed to connect the service to the hub server",
				zap.Error(err),
			)
			continue
		}

		hub.Log.Info("Service connected to hub server",
			zap.String("addr", service.Addr),
		)

		service.Run()
		// TODO: delete
		//go func() {
		//	timer := time.NewTimer(time.Second * 5)
		//	<-timer.C
		//	tmpInitialGame(conn, 1) // n - number champs
		//}()
	}
}
