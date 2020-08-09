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
	srvStopped          = "Stopped Service"
	failCreateNewWorker = "Failed to create Worker"
	failApplyTCPSetting = "Failed to Apply TCPSettings to Worker"
	launchNewWorker     = "Launched the new worker"
	initSizeWorkersMap  = 8
)

type Service struct {
	Type    int
	Addr    string
	Log     *zap.Logger
	Conf    ServiceConf
	Workers *SyncMap
	parent  *ServiceManage
	conn    *net.TCPConn
	ctx     context.Context
	cancel  context.CancelFunc
	pool    *PoolMessages
	stopped chan string
}

func NewUndefinedService(manager *ServiceManage, conn *net.TCPConn) (*Service, error) {
	log, e := zap.NewProduction()
	if e != nil {
		return nil, e
	}
	ctx, cancel := context.WithCancel(context.Background())
	return &Service{
		Type:    ServiceTypeUndefined,
		Addr:    conn.RemoteAddr().String(),
		Log:     log,
		Workers: NewSyncMap(initSizeWorkersMap),
		parent:  manager,
		conn:    conn,
		ctx:     ctx,
		pool:    NewPoolMessages(ServiceTypeUndefined),
		cancel:  cancel,
	}, nil
}

func (srv *Service) Run() {
	srv.HandleFuncLoop(handleService)
	go func() {
		select {
		case <-srv.parent.ctx.Done():
			srv.Stop()
		case <-srv.ctx.Done():
			return
		}
	}()
}

func (srv *Service) Stop() {
	if srv.Log != nil {
		srv.Log.Info(srvStopped,
			zap.String("addr", srv.Addr),
			zap.Int("type", srv.Type),
		)
		_ = srv.Log.Sync()
	}
	if srv.conn != nil {
		_ = srv.conn.Close()
	}
	srv.cancel()
}

func (srv *Service) HandleFuncLoop(handler func(s *Service)) {
	go func() {
		for {
			select {
			case <-srv.parent.ctx.Done():
				return
			case <-srv.ctx.Done():
				return
			default:
				handler(srv)
			}
		}
	}()
}

func (srv *Service) RegisterServiceTypeVM() {
	srv.Type = ServiceTypeVM
	srv.Conf = srv.parent.Conf.ServiceVM
	srv.pool = NewPoolMessages(ServiceTypeVM)
}

func (srv *Service) RegisterServiceTypeASM() {
	srv.Type = ServiceTypeASM
	srv.Conf = srv.parent.Conf.ServiceASM
	srv.pool = NewPoolMessages(ServiceTypeASM)
}

func (srv *Service) RunWorkers(n int, handler func(wrk *Worker)) {
	for n > 0 {
		// Create New Worker
		listener, e := net.ListenTCP("tcp", nil)
		if e != nil {
			srv.Log.Error(failCreateNewWorker,
				zap.String("addr", srv.Addr),
				zap.Int("type", srv.Type),
				zap.Error(e),
			)
			n--
			continue
		}
		if e = srv.Conf.WorkerConf.ApplyToListener(listener); e != nil {
			srv.Log.Error(failApplyTCPSetting,
				zap.String("addr", srv.Addr),
				zap.Int("type", srv.Type),
			)
		}

		log, e := zap.NewProduction()
		if e != nil {
			srv.Log.Error(failCreateNewWorker,
				zap.String("addr", srv.Addr),
				zap.Int("type", srv.Type),
				zap.Error(e),
			)
			_ = listener.Close()
			n--
			continue
		}

		ctx, cancel := context.WithCancel(context.Background())

		worker := &Worker{
			addr:     listener.Addr().String(),
			listener: listener,
			conf:     srv.Conf.WorkerConf,
			log:      log,
			pctx:     srv.ctx,
			ctx:      ctx,
			cancel:   cancel,
			parent:   srv,
			handler:  handler,
			pool:     NewPoolMessages(srv.Type),
		}

		worker.Run()
		srv.Workers.Store(worker.addr, worker)
		srv.Log.Info(launchNewWorker,
			zap.String("addr", worker.addr),
		)
		n--
	}
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
//	fmt.Printf("ConnectNewService worker conn %v\n", conn.RemoteAddr().String())
////			go handleConnection(conn, nil, handleGameWorker)
////			case <-ctx.Done():
////				break
//}
//}()
//}
//
