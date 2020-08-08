package main

import "go.uber.org/zap"

const (
	errorReadHeader      = "Error reading header"
	errorSendHandshakeVM = "Error sending handshakeVM message"
	errorRunWorker       = "Error running worker"
	receivedHandshakeVM  = "Received a handshakeVM message"
	sentHandshakeVM      = "Sent a handshakeVM message"
)

func handleService(srv *Service) {
	var (
		h *Header
		e error
	)

	h = headerPool.Get().(*Header)
	if e = h.Read(srv.conn); e != nil {
		srv.Log.Error(errorReadHeader, zap.String("addr", srv.Addr), zap.Error(e))
		return
	}

	switch h.Type {
	case TypeMsgHandshakeVM:
		msg := handshakeVMPool.Get().(*HandshakeVM)
		msg.SetHeader(h)
		srv.Log.Info(receivedHandshakeVM, zap.String("addr", srv.Addr))

		// service registration
		srv.Type = ServiceTypeVM
		srv.Conf = srv.parent.Conf.ServiceVM

		// TODO: implement handler
		if e = srv.RunWorkers(int(msg.NumWorkers), nil); e != nil {
			srv.Log.Error(errorRunWorker,
				zap.String("addr", srv.Addr),
				zap.Int("type", srv.Type),
				zap.Error(e),
			)
			return
		}

		if e = msg.Write(srv.conn); e != nil {
			srv.Log.Error(errorSendHandshakeVM,
				zap.String("addr", srv.Addr),
				zap.Int("type", srv.Type),
				zap.Error(e),
			)
			return
		}
		srv.Log.Info(sentHandshakeVM,
			zap.String("addr", srv.Addr),
			zap.Int("type", srv.Type),
			zap.Error(e),
		)
	case TypeMsgGameNotification:
		// TODO: handleGameNotification(srv)
	case TypeMsgHandshakeASM:
		// TODO: handleHandshakeASM(srv)
	}
}
