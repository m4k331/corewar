package main

import (
	"context"
	"go.uber.org/zap"
	"net"
)

type Worker struct {
	addr     string
	listener *net.TCPListener
	conf     WorkerConf
	log      *zap.Logger
	pctx     context.Context
	ctx      context.Context
	cancel   context.CancelFunc
	parent   *Service
	pool     *PoolMessages
	handler  func(wrk *Worker)
	execs    map[uint32]*Executor
}

func (wrk *Worker) Run() {
	wrk.HandleFuncLoop(wrk.handler)
	go func() {
		select {
		case <-wrk.parent.ctx.Done():
			wrk.Stop()
		case <-wrk.ctx.Done():
			return
		}
	}()
}

func (wrk *Worker) Stop() {
	if wrk.log != nil {
		wrk.log.Info(srvStopped, zap.String("addr", wrk.addr))
		_ = wrk.log.Sync()
	}
	if wrk.listener != nil {
		_ = wrk.listener.Close()
	}
	wrk.cancel()
}

func (wrk *Worker) HandleFuncLoop(handler func(s *Worker)) {
	go func() {
		for {
			select {
			case <-wrk.parent.ctx.Done():
				return
			case <-wrk.ctx.Done():
				return
			default:
				handler(wrk)
			}
		}
	}()
}

type Executor struct {
	conn *net.TCPConn
	ctx  context.Context
	port uint32
}

//func (wrk *Worker) AddNewExecutor() error {
//	conn, err := wrk.listener.AcceptTCP()
//	if err != nil {
//		return err
//	}
//	if err = wrk.parent.conf.ApplyToConnection(conn); err != nil {
//		return err
//	}
//	wrk.execs = append(wrk.execs, &Executor{
//		conn: conn,
//		ctx:  wrk.ctx,
//		port: ExtractPort(conn.RemoteAddr().String()),
//	})
//	return err
//}
