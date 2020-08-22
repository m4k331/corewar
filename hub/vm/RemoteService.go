package main

import (
	"context"
	"corewar/hub/syncd"
	"go.uber.org/zap"
	"net"
)

const (
	ServiceTypeUndefined = iota
	ServiceTypeVM
	ServiceTypeASM
)

const (
	srvStopped          = "Stopped RemoteService"
	failApplyTCPSetting = "Failed to Apply TCPSettings"
	failLaunchNewWorker = "Failed launch the new worker"
	launchNewWorker     = "Launched the new worker"
	initSizeWorkersMap  = 8
)

type RemoteService struct {
	code    int
	conn    *net.TCPConn
	conf    ServiceConf
	log     *zap.Logger
	ctx     context.Context
	cancel  context.CancelFunc
	master  Service
	slaves  *syncd.Map
	pool    *PoolMessages
	handler HandleServiceFunc
	stopped chan string
}

func NewRemoteService(manager Service, conn *net.TCPConn, handler HandleServiceFunc) (*RemoteService, error) {
	log, e := zap.NewProduction()
	if e != nil {
		return nil, e
	}
	ctx, cancel := context.WithCancel(context.Background())
	return &RemoteService{
		code:    ServiceTypeUndefined,
		conn:    conn,
		log:     log,
		ctx:     ctx,
		cancel:  cancel,
		master:  manager,
		slaves:  syncd.NewMap(initSizeWorkersMap),
		handler: handler,
		pool:    NewPoolMessages(ServiceTypeUndefined),
	}, nil
}

func (srv *RemoteService) Run() {
	srv.RunHandleFuncLoop()
	go func() {
		select {
		case <-srv.master.GetCtx().Done():
			srv.Stop()
		case <-srv.ctx.Done():
			return
		}
	}()
}

func (srv *RemoteService) Stop() {
	if srv.log != nil {
		srv.log.Info(srvStopped,
			zap.String("addr", srv.GetAddr()),
			zap.Int("type", srv.GetCode()),
		)
		_ = srv.log.Sync()
	}
	if srv.conn != nil {
		_ = srv.conn.Close()
	}
	srv.cancel()
}

func (srv *RemoteService) RunHandleFunc() {
	srv.handler(srv)
}

func (srv *RemoteService) RunHandleFuncLoop() {
	go func() {
		for {
			select {
			case <-srv.master.GetCtx().Done():
				return
			case <-srv.ctx.Done():
				return
			default:
				srv.RunHandleFunc()
			}
		}
	}()
}

func (srv *RemoteService) RunNewSlave() error {
	worker, e := NewWorker(srv, handleWorker)
	if e != nil {
		srv.log.Info(failLaunchNewWorker, zap.Error(e))
		return e
	}

	worker.Run()
	srv.slaves.Store(worker.GetAddr(), worker)
	srv.log.Info(launchNewWorker,
		zap.String("addr", worker.GetAddr()),
	)
	return e
}

func (srv *RemoteService) GetCode() int {
	return srv.code
}

func (srv *RemoteService) GetAddr() string {
	return srv.conn.RemoteAddr().String()
}

func (srv *RemoteService) GetListener() *net.TCPListener {
	return nil
}

func (srv *RemoteService) GetConn() *net.TCPConn {
	return srv.conn
}

func (srv *RemoteService) GetMaster() Service {
	return srv.master
}

func (srv *RemoteService) GetConfig() interface{} {
	return srv.conf
}

func (srv *RemoteService) GetLog() *zap.Logger {
	return srv.log
}

func (srv *RemoteService) GetCtx() context.Context {
	return srv.ctx
}

func (srv *RemoteService) GetCtxCancel() context.CancelFunc {
	return srv.cancel
}

func (srv *RemoteService) GetPool() *PoolMessages {
	return srv.pool
}

func (srv *RemoteService) GetHandler() HandleServiceFunc {
	return srv.handler
}

func (srv *RemoteService) GetSlaves() *syncd.Map {
	return srv.slaves
}

func (srv *RemoteService) SetCode(code int) {
	srv.code = code
}

func (srv *RemoteService) SetConfig(config interface{}) {
	srv.conf = config.(ServiceConf)
}

func (srv *RemoteService) SetPool(pool *PoolMessages) {
	srv.pool = pool
}
