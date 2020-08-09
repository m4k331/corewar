package main

import (
	"context"
	"go.uber.org/zap"
	"net"
)

const (
	failedCreateNewConn = "Failed to create a new connection"
	failedApplySettings = "Failed to apply settings"
	connSrvInterrupted  = "The connection to the new service was interrupted"
	addedNewService     = "Successfully added a new service"
	smStopped           = "Stopped ServiceManage"
	successConnToManage = "RemoteService connected to ServiceManage"
	failedConnToManage  = "Failed to connect the service to ServiceManage"
	initSizeServicesMap = 8
)

type ServiceManage struct {
	code     int
	listener *net.TCPListener
	conf     Config
	log      *zap.Logger
	ctx      context.Context
	cancel   context.CancelFunc
	slaves   *SyncMap
	handler  HandleServiceFunc
	stopped  chan string
}

func NewServiceManage(config Config) (*ServiceManage, error) {
	log, e := zap.NewProduction()
	if e != nil {
		return nil, e
	}

	addr, e := net.ResolveTCPAddr("tcp", config.ServiceManage.Addr)
	if e != nil {
		_ = log.Sync()
		return nil, e
	}

	listener, e := net.ListenTCP("tcp", addr)
	if e != nil {
		_ = log.Sync()
		return nil, e
	}
	e = config.ServiceManage.TCPSettings.ApplyToListener(listener)

	ctx, cancel := context.WithCancel(context.Background())

	return &ServiceManage{
		listener: listener,
		conf:     config,
		log:      log,
		ctx:      ctx,
		cancel:   cancel,
		slaves:   NewSyncMap(initSizeServicesMap),
		handler:  handleServiceManage,
		stopped:  make(chan string, config.ServiceManage.MaxNumChild),
	}, e
}

func (sm *ServiceManage) Run() {
	// a handler that clears the service list of stopped services
	go func() {
		for {
			select {
			case <-sm.ctx.Done():
				return
			case addr := <-sm.stopped:
				sm.slaves.Delete(addr)
			}
		}
	}()
	sm.RunHandleFuncLoop()
}

func (sm *ServiceManage) RunHandleFunc() {
	sm.handler(sm)
}

func (sm *ServiceManage) RunHandleFuncLoop() {
	for {
		sm.RunHandleFunc()
	}
}

func (sm *ServiceManage) RunNewSlave() (e error) {
	conn, e := sm.listener.AcceptTCP()
	if e != nil {
		return CloseFailedConnection(conn, sm.log, failedCreateNewConn, e)
	}
	if e = sm.conf.ServiceManage.TCPSettings.ApplyToConnection(conn); e != nil {
		return CloseFailedConnection(conn, sm.log, failedApplySettings, e)
	}

	srv, e := NewRemoteService(sm, conn, handleService)
	if e != nil {
		return CloseFailedConnection(conn, sm.log, connSrvInterrupted, e)
	}

	sm.slaves.Store(srv.GetAddr(), srv)
	sm.log.Info(addedNewService, zap.String("addr", srv.GetAddr()))

	srv.Run()
	sm.log.Info(successConnToManage, zap.String("addr", srv.GetAddr()))
	return e
}

func (sm *ServiceManage) Stop() {
	if sm.log != nil {
		sm.log.Info(smStopped, zap.String("addr", sm.GetAddr()))
		_ = sm.log.Sync()
	}
	if sm.listener != nil {
		_ = sm.listener.Close()
	}
	sm.cancel()
}

func (sm *ServiceManage) GetCode() int {
	return sm.code
}

func (sm *ServiceManage) GetAddr() string {
	return sm.listener.Addr().String()
}

func (sm *ServiceManage) GetListener() *net.TCPListener {
	return sm.listener
}

func (sm *ServiceManage) GetConn() *net.TCPConn {
	return nil
}

func (sm *ServiceManage) GetMaster() Service {
	return nil
}

func (sm *ServiceManage) GetConfig() interface{} {
	return sm.conf
}

func (sm *ServiceManage) GetLog() *zap.Logger {
	return sm.log
}

func (sm *ServiceManage) GetCtx() context.Context {
	return sm.ctx
}

func (sm *ServiceManage) GetCtxCancel() context.CancelFunc {
	return sm.cancel
}

func (sm *ServiceManage) GetPool() *PoolMessages {
	return nil
}

func (sm *ServiceManage) GetHandler() HandleServiceFunc {
	return sm.handler
}

func (sm *ServiceManage) GetSlaves() *SyncMap {
	return sm.slaves
}

func (sm *ServiceManage) SetCode(code int) {
	sm.code = code
}

func (sm *ServiceManage) SetConfig(config interface{}) {
	sm.conf = config.(Config)
}

func (sm *ServiceManage) SetPool(pool *PoolMessages) {
	_ = pool
}
