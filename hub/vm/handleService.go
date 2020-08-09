package main

import "go.uber.org/zap"

const (
	errorReadHeader      = "Error reading header"
	errorSendHandshakeVM = "Error sending handshakeVM message"
	receivedHandshakeVM  = "Received a handshakeVM message"
	sentHandshakeVM      = "Sent a handshakeVM message"
)

// TODO: подумать над тем как реагировать если сообщение пришло не валидное
func handleService(srv *Service) {
	h := srv.pool.Get(TypeMsgHeader).(*Header)
	e := h.Read(srv.conn)
	if e != nil {
		srv.Log.Error(errorReadHeader, zap.String("addr", srv.Addr), zap.Error(e))
		return
	}

	switch h.Type {
	case TypeMsgHandshakeVM:
		msg := srv.pool.Get(TypeMsgHandshakeVM).(*Handshake)
		msg.SetHeader(h)
		srv.Log.Info(receivedHandshakeVM, zap.String("addr", srv.Addr))

		srv.RegisterServiceTypeVM()

		// TODO: implement handler
		srv.RunWorkers(int(msg.Len), nil)

		// TODO: impl prepare ports for msg
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
