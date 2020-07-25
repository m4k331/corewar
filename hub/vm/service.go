package main

import (
	"context"
	"fmt"
	"go.uber.org/zap"
	"net"
)

const (
	ServiceTypeUndefined = iota
	ServiceTypeVM
	ServiceTypeASM
)

type Service struct {
	Type    int
	Addr    string
	Log     *zap.Logger
	conn    *net.TCPConn
	parent  *ServiceManage
	pctx    context.Context
	ctx     context.Context
	cancel  context.CancelFunc
	kill    chan struct{}
	conf    ServiceConf
	workers []*Worker
}

func handleExecutor(wrk *Worker) {
	go func() {
		defer func() {
			// TODO: close worker
		}()
		if err := wrk.AddNewExecutor(); err != nil {
		}

		chanConn := make(chan net.Conn)
		go func() {
			for {
				accept, err := wrk.listener.Accept()
				if err != nil {
					continue
				}
				chanConn <- accept
				break
			}
		}()
		select {
		case conn := <-chanConn:
			fmt.Printf("ConnectNewService worker conn %v\n", conn.RemoteAddr().String())
			//go handleConnection(conn, nil, handleGameWorker)
			//case <-ctx.Done():
			//	break
		}
	}()
}

func (srv *Service) RunWorkers(n int, handler func(wrk *Worker)) error {
	var (
		err  error
		fail int
	)

	for n > 0 {
		worker := &Worker{
			parent: srv,
			pctx:   srv.ctx,
			execs:  make([]*Executor, 0, 8),
		}

		worker.listener, err = net.ListenTCP("tcp", nil)
		worker.listener.SetDeadline()
		if err != nil {
			srv.Log.Error("Failed to create worker",
				zap.String("addr", srv.Addr),
				zap.Int("type", srv.Type),
				zap.Error(err),
			)
			fail++
			n--
			continue
		}

		worker.addr = worker.listener.Addr().String()
		worker.ctx, worker.cancel = context.WithCancel(context.Background())

		srv.Log.Info("Launched the new worker",
			zap.String("addr", worker.addr),
		)

		handler(worker)

		n--
	}

	if fail > 0 {
		err = fmt.Errorf("Failed to launch workers %d/%d ", fail, n)
	}
	return err
}

func (srv *Service) Stop() {
	srv.Log.Info("Stopped Service",
		zap.String("addr", srv.Addr),
		zap.Int("type", srv.Type),
	)
	srv.cancel()
	_ = srv.conn.Close()
	_ = srv.Log.Sync()
}

func (srv *Service) HandleFuncLoop(handler func(s *Service)) {
	go func() {
		for {
			select {
			case <-srv.ctx.Done():
				srv.Log.Info("Stopped HandleFuncLoop",
					zap.String("addr", srv.Addr),
					zap.Int("type", srv.Type),
				)
			default:
				handler(srv)
			}
		}
	}()
}

func (srv *Service) Run() {
	srv.HandleFuncLoop(handleService)
	go func() {
		select {
		case <-srv.pctx.Done():
			srv.Stop()
		case <-srv.kill:
			srv.Stop()
		}
	}()
}
