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
	smAddedNewService   = "ServiceManage has successfully added a new service"
	smStopped           = "Stopped ServiceManage"
	initSizeServicesMap = 8
)

type ServiceManage struct {
	Addr     string
	Conf     *Config
	Services *SyncMap
	Log      *zap.Logger
	stopped  chan string
	listen   *net.TCPListener
	ctx      context.Context
	cancel   context.CancelFunc
}

func NewServiceManage(config *Config) (*ServiceManage, error) {
	var (
		e  error
		sm = new(ServiceManage)
	)

	sm.Log, e = zap.NewProduction()
	if e != nil {
		return nil, e
	}
	if e = sm.Listen(); e != nil {
		_ = sm.Log.Sync()
		return nil, e
	}

	sm.Addr = sm.listen.Addr().String()
	sm.Conf = config
	sm.Services = NewSyncMap(initSizeServicesMap)
	sm.stopped = make(chan string, config.ServiceManage.MaxNumChild)
	sm.ctx, sm.cancel = context.WithCancel(context.Background())

	// a handler that clears the service list of stopped services
	go func() {
		for {
			select {
			case <-sm.ctx.Done():
				return
			case addr := <-sm.stopped:
				sm.Services.Delete(addr)
			}
		}
	}()

	return sm, e
}

func (sm *ServiceManage) Listen() (e error) {
	addr, e := net.ResolveTCPAddr("tcp", sm.Conf.ServiceManage.Addr)
	if e != nil {
		return e
	}
	sm.listen, e = net.ListenTCP("tcp", addr)
	if e != nil {
		return e
	}
	e = sm.Conf.ServiceManage.TCPSettings.ApplyToListener(sm.listen)
	return e
}

func (sm *ServiceManage) Stop() {
	if sm.Log != nil {
		sm.Log.Info(smStopped, zap.String("addr", sm.Addr))
		_ = sm.Log.Sync()
	}
	if sm.listen != nil {
		_ = sm.listen.Close()
	}
	sm.cancel()
}

func (sm *ServiceManage) ConnectNewService() (*Service, error) {
	conn, e := sm.listen.AcceptTCP()
	if e != nil {
		return nil, CloseFailedConnection(conn, sm.Log, failedCreateNewConn, e)
	}
	if e = sm.Conf.ServiceManage.TCPSettings.ApplyToConnection(conn); e != nil {
		return nil, CloseFailedConnection(conn, sm.Log, failedApplySettings, e)
	}
	srv, e := NewUndefinedService(sm, conn)
	if e != nil {
		return nil, CloseFailedConnection(conn, sm.Log, connSrvInterrupted, e)
	}
	sm.Services.Store(srv.Addr, srv)
	sm.Log.Info(smAddedNewService, zap.String("addr", srv.Addr))
	return srv, e
}
