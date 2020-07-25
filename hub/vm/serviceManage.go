package main

import (
	"context"
	"go.uber.org/zap"
	"net"
)

type ServiceManage struct {
	Addr     string
	Conf     *Config
	Log      *zap.Logger
	listen   *net.TCPListener
	ctx      context.Context
	cancel   context.CancelFunc
	services map[string]*Service
}

// TODO: implement ServiceManage STOP()

func NewServiceManage(config *Config) (*ServiceManage, error) {
	var (
		err error
		sm  = new(ServiceManage)
	)

	sm.Log, err = zap.NewProduction()
	if err != nil {
		return nil, err
	}

	sm.listen, err = net.ListenTCP("tcp", config.ServiceManage.AddrTCP)
	if err != nil {
		_ = sm.Log.Sync()
		return nil, err
	}

	sm.Addr = sm.listen.Addr().String()
	sm.Conf = config
	sm.ctx, sm.cancel = context.WithCancel(context.Background())
	sm.services = make(map[string]*Service, 8)

	return sm, err
}

func (sm *ServiceManage) ConnectNewService() (*Service, error) {
	conn, err := sm.listen.AcceptTCP()
	if err != nil {
		return nil, err
	}

	// keep_alive connection setup
	if err = sm.Conf.ServiceManage.ApplyToConnection(conn); err != nil {
		_ = conn.Close()
		return nil, err
	}

	// create new service
	srv := &Service{
		Type:    ServiceTypeUndefined,
		Addr:    conn.RemoteAddr().String(),
		conn:    conn,
		parent:  sm,
		pctx:    sm.ctx,
		kill:    make(chan struct{}, 1),
		workers: make([]*Worker, 0, 8),
	}
	srv.Log, err = zap.NewProduction()
	if err != nil {
		_ = conn.Close()
		return nil, err
	}
	srv.ctx, srv.cancel = context.WithCancel(context.Background())

	// add new service
	sm.services[srv.Addr] = srv

	return srv, err
}
