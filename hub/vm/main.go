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

const (
	startHubServer         = "Start hub server"
	failedConnToHubServer  = "Failed to connect the service to the hub server"
	successConnToHubServer = "Service connected to hub server"
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
	hub.Log.Info(startHubServer, zap.String("addr", hub.Addr))

	for {
		service, err := hub.ConnectNewService()
		if err != nil {
			hub.Log.Error(failedConnToHubServer, zap.Error(err))
			continue
		}

		hub.Log.Info(successConnToHubServer, zap.String("addr", service.Addr))

		service.Run()
	}
}
