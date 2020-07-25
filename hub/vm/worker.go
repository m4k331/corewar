package main

import (
	"context"
	"net"
)

type Worker struct {
	listener *net.TCPListener
	addr     string
	pctx     context.Context
	ctx      context.Context
	cancel   context.CancelFunc
	parent   *Service
	execs    []*Executor
}

type Executor struct {
	conn *net.TCPConn
	ctx  context.Context
	port uint32
}

func (wrk *Worker) AddNewExecutor() error {
	conn, err := wrk.listener.AcceptTCP()
	if err != nil {
		return err
	}
	if err = wrk.parent.conf.ApplyToConnection(conn); err != nil {
		return err
	}
	wrk.execs = append(wrk.execs, &Executor{
		conn: conn,
		ctx:  wrk.ctx,
		port: ExtractPort(conn.RemoteAddr().String()),
	})
	return err
}
