package main

import (
	"context"
	"corewar/hub/syncd"
	"go.uber.org/zap"
	"net"
)

type Worker struct {
	code     int
	listener *net.TCPListener
	conf     WorkerConf
	log      *zap.Logger
	ctx      context.Context
	cancel   context.CancelFunc
	master   Service
	slaves   *syncd.Map
	pool     *PoolMessages
	handler  HandleServiceFunc
}

func NewWorker(s Service, handler HandleServiceFunc) (*Worker, error) {
	listener, e := net.ListenTCP("tcp", nil)
	if e != nil {
		return nil, e
	}
	e = s.GetConfig().(ServiceConf).WorkerConf.ApplyToListener(listener)
	if e != nil {
		s.GetLog().Error(failApplyTCPSetting,
			zap.String("addr", s.GetAddr()),
			zap.Int("type", s.GetCode()),
		)
	}

	log, e := zap.NewProduction()
	if e != nil {
		_ = listener.Close()
		return nil, e
	}

	ctx, cancel := context.WithCancel(context.Background())

	return &Worker{
		listener: listener,
		conf:     s.GetConfig().(ServiceConf).WorkerConf,
		log:      log,
		ctx:      ctx,
		cancel:   cancel,
		master:   s,
		handler:  handler,
		pool:     NewPoolMessages(s.GetCode()),
	}, e
}

func (wrk *Worker) Run() {
	go func() {
		select {
		case <-wrk.master.GetCtx().Done():
			wrk.Stop()
		case <-wrk.ctx.Done():
			return
		}
	}()
	wrk.RunHandleFunc()
}

func (wrk *Worker) Stop() {
	if wrk.log != nil {
		wrk.log.Info(srvStopped, zap.String("addr", wrk.GetAddr()))
		_ = wrk.log.Sync()
	}
	if wrk.listener != nil {
		_ = wrk.listener.Close()
	}
	wrk.cancel()
}

func (wrk *Worker) RunHandleFunc() {
	wrk.handler(wrk)
}

func (wrk *Worker) RunHandleFuncLoop() {
	go func() {
		for {
			select {
			case <-wrk.master.GetCtx().Done():
				return
			case <-wrk.ctx.Done():
				return
			default:
				wrk.RunHandleFunc()
			}
		}
	}()
}

func (wrk *Worker) RunNewSlave() error {
	return nil
}

func (wrk *Worker) GetAddr() string {
	return wrk.listener.Addr().String()
}

func (wrk *Worker) GetListener() *net.TCPListener {
	return wrk.listener
}

func (wrk *Worker) GetConn() *net.TCPConn {
	return nil
}

func (wrk *Worker) GetMaster() Service {
	return wrk.master
}

func (wrk *Worker) GetConfig() interface{} {
	return wrk.conf
}

func (wrk *Worker) GetLog() *zap.Logger {
	return wrk.log
}

func (wrk *Worker) GetCtx() context.Context {
	return wrk.ctx
}

func (wrk *Worker) GetCtxCancel() context.CancelFunc {
	return wrk.cancel
}

func (wrk *Worker) GetPool() *PoolMessages {
	return wrk.pool
}

func (wrk *Worker) GetHandler() HandleServiceFunc {
	return wrk.handler
}

func (wrk *Worker) GetSlaves() *syncd.Map {
	return wrk.slaves
}

func (wrk *Worker) GetCode() int {
	return wrk.code
}

func (wrk *Worker) SetCode(code int) {
	wrk.code = code
}

func (wrk *Worker) SetConfig(config interface{}) {
	wrk.conf = config.(WorkerConf)
}

func (wrk *Worker) SetPool(pool *PoolMessages) {
	wrk.pool = pool
}
