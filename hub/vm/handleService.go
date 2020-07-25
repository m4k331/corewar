package main

import "go.uber.org/zap"

func handleService(srv *Service) {
	var (
		typeMsg uint8
		err     error
	)

	typeMsg, err = ReadTypeMsg(srv.conn)
	if err != nil {
		srv.Log.Error("Error reading type message",
			zap.String("addr", srv.Addr),
			zap.Error(err),
		)
		return
	}

	switch typeMsg {
	case TypeMsgHandshakeVM:
		msg := new(HandshakeVM)
		if err := msg.Read(srv.conn); err != nil {
			srv.Log.Error("Error reading handshakeVM message",
				zap.String("addr", srv.Addr),
				zap.Error(err),
			)
			return
		}
		srv.Log.Info("Received a handshakeVM message",
			zap.String("addr", srv.Addr),
		)

		// service registration
		srv.Type = ServiceTypeVM
		srv.conf = srv.parent.Conf.Service[ServiceTypeVM]

		// TODO: implement handler
		if err = srv.RunWorkers(int(msg.NumWorkers), nil); err != nil {
			srv.Log.Error("Error sending handshakeVM message",
				zap.String("addr", srv.Addr),
				zap.Int("type", srv.Type),
				zap.Error(err),
			)
			return
		}

		if err = msg.Write(srv.conn); err != nil {
			srv.Log.Error("Error sending handshakeVM message",
				zap.String("addr", srv.Addr),
				zap.Int("type", srv.Type),
				zap.Error(err),
			)
			return
		}
		srv.Log.Info("Sent a handshakeVM message",
			zap.String("addr", srv.Addr),
			zap.Int("type", srv.Type),
			zap.Error(err),
		)
	case TypeMsgGameNotification:
		// TODO: handleGameNotification(srv)
	case TypeMsgHandshakeASM:
		// TODO: handleHandshakeASM(srv)
	}
}
