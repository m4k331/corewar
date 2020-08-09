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
	srvStopped         = "Stopped Service"
	initSizeWorkersMap = 8
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
//func (srv *Service) RunWorkers(n int, handler func(wrk *Worker)) error {
//	var (
//		err  error
//		fail int
//	)
//
//	for n > 0 {
//		worker := &Worker{
//			parent: srv,
//			pctx:   srv.ctx,
//			execs:  make([]*Executor, 0, 8),
//		}
//
//		worker.listener, err = net.ListenTCP("tcp", nil)
////		worker.parent.conf.
//if err != nil {
//	srv.Log.Error("Failed to create worker",
//		zap.String("addr", srv.Addr),
//		zap.Int("type", srv.Type),
//		zap.Error(err),
//	)
//	fail++
//	n--
//	continue
//}
//
//worker.addr = worker.listener.Addr().String()
//worker.ctx, worker.cancel = context.WithCancel(context.Background())
//
//srv.Log.Info("Launched the new worker",
//	zap.String("addr", worker.addr),
//)
//
//handler(worker)
//
//n--
//}
//
//if fail > 0 {
//	err = fmt.Errorf("Failed to launch workers %d/%d ", fail, n)
//}
//return err
//}
//
