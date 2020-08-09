package main

import (
	"context"
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
	failApplyTCPSetting = "Failed to Apply TCPSettings to Worker"
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
	slaves  *SyncMap
	pool    *PoolMessages
	handler HandleServiceFunc
	stopped chan string
}

func NewUndefinedRemoteService(manager Service, conn *net.TCPConn) (*RemoteService, error) {
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
		slaves:  NewSyncMap(initSizeWorkersMap),
		handler: handleService,
		pool:    NewPoolMessages(ServiceTypeUndefined),
	}, nil
}

func (srv *RemoteService) Run() {
	srv.HandleFuncLoop(srv.handler)
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

func (srv *RemoteService) HandleFuncLoop(handler HandleServiceFunc) {
	go func() {
		for {
			select {
			case <-srv.master.GetCtx().Done():
				return
			case <-srv.ctx.Done():
				return
			default:
				handler(srv)
			}
		}
	}()
}

func (srv *RemoteService) RunNewSlave() error {
	// Create New Worker
	listener, e := net.ListenTCP("tcp", nil)
	if e != nil {
		return e
	}
	if e = srv.conf.WorkerConf.ApplyToListener(listener); e != nil {
		srv.log.Error(failApplyTCPSetting,
			zap.String("addr", srv.GetAddr()),
			zap.Int("type", srv.code),
		)
	}

	log, e := zap.NewProduction()
	if e != nil {
		_ = listener.Close()
		return e
	}

	ctx, cancel := context.WithCancel(context.Background())

	var handler HandleServiceFunc
	switch srv.code {
	case ServiceTypeVM:
		handler = nil // TODO: impl handler
	}

	worker := &Worker{
		listener: listener,
		conf:     srv.conf.WorkerConf,
		log:      log,
		ctx:      ctx,
		cancel:   cancel,
		master:   srv,
		handler:  handler,
		pool:     NewPoolMessages(srv.code),
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

func (srv *RemoteService) GetSlaves() *SyncMap {
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

//func handleExecutor(wrk *Worker) {
//	go func() {
//		defer func() {
////			TODO: close worker
//}()
//if err := wrk.AddNewExecutor(); err != nil {
//}
//
//chanConn := make(chan net.Conn)
//go func() {
//	for {
//		accept, err := wrk.listener.Accept()
//		if err != nil {
//			continue
//		}
//		chanConn <- accept
//		break
//	}
//}()
//select {
//case conn := <-chanConn:
//	fmt.Printf("ConnectNewRemoteService worker conn %v\n", conn.RemoteAddr().String())
////			go handleConnection(conn, nil, handleGameWorker)
////			case <-ctx.Done():
////				break
//}
//}()
//}
//
