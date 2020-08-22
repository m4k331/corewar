package main

import (
	"context"
	"corewar/hub/syncd"
	"go.uber.org/zap"
	"net"
)

type HandleServiceFunc func(s Service)

type Service interface {
	Run()
	Stop()
	RunHandleFunc()
	RunHandleFuncLoop()
	RunNewSlave() error
	GetCode() int
	GetAddr() string
	GetListener() *net.TCPListener
	GetConn() *net.TCPConn
	GetMaster() Service
	GetConfig() interface{}
	GetLog() *zap.Logger
	GetCtx() context.Context
	GetCtxCancel() context.CancelFunc
	GetPool() *PoolMessages
	GetHandler() HandleServiceFunc
	GetSlaves() *syncd.Map
	SetCode(code int)
	SetConfig(config interface{})
	SetPool(pool *PoolMessages)
}
