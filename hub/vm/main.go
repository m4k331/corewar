package main

import (
	"go.uber.org/zap"
)

const (
	ConfigPath     = "/home/ahugh/go/cw/hub/vm/config/config.yaml"
	startHubServer = "Start hub server"
)

func main() {
	config, err := NewConfig(ConfigPath)
	if err != nil {
		panic(err)
	}

	hub, err := NewServiceManage(*config)
	if err != nil {
		panic(err)
	}
	hub.log.Info(startHubServer, zap.String("addr", hub.GetAddr()))
	hub.Run()
}
