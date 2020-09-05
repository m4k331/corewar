package main

import (
	"context"
	"cw/hub/syncd"
	"go.uber.org/zap"
	"net"
)

type WorkerTODO struct {
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

func NewWorker(s Service, handler HandleServiceFunc) (*WorkerTODO, error) {
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

	return &WorkerTODO{
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

func (wrk *WorkerTODO) Run() {
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

func (wrk *WorkerTODO) Stop() {
	if wrk.log != nil {
		wrk.log.Info(srvStopped, zap.String("addr", wrk.GetAddr()))
		_ = wrk.log.Sync()
	}
	if wrk.listener != nil {
		_ = wrk.listener.Close()
	}
	wrk.cancel()
}

func (wrk *WorkerTODO) RunHandleFunc() {
	wrk.handler(wrk)
}

func (wrk *WorkerTODO) RunHandleFuncLoop() {
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

func (wrk *WorkerTODO) RunNewSlave() error {
	return nil
}

func (wrk *WorkerTODO) GetAddr() string {
	return wrk.listener.Addr().String()
}

func (wrk *WorkerTODO) GetListener() *net.TCPListener {
	return wrk.listener
}

func (wrk *WorkerTODO) GetConn() *net.TCPConn {
	return nil
}

func (wrk *WorkerTODO) GetMaster() Service {
	return wrk.master
}

func (wrk *WorkerTODO) GetConfig() interface{} {
	return wrk.conf
}

func (wrk *WorkerTODO) GetLog() *zap.Logger {
	return wrk.log
}

func (wrk *WorkerTODO) GetCtx() context.Context {
	return wrk.ctx
}

func (wrk *WorkerTODO) GetCtxCancel() context.CancelFunc {
	return wrk.cancel
}

func (wrk *WorkerTODO) GetPool() *PoolMessages {
	return wrk.pool
}

func (wrk *WorkerTODO) GetHandler() HandleServiceFunc {
	return wrk.handler
}

func (wrk *WorkerTODO) GetSlaves() *syncd.Map {
	return wrk.slaves
}

func (wrk *WorkerTODO) GetCode() int {
	return wrk.code
}

func (wrk *WorkerTODO) SetCode(code int) {
	wrk.code = code
}

func (wrk *WorkerTODO) SetConfig(config interface{}) {
	wrk.conf = config.(WorkerConf)
}

func (wrk *WorkerTODO) SetPool(pool *PoolMessages) {
	wrk.pool = pool
}
