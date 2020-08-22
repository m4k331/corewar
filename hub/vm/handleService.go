package main

import "go.uber.org/zap"

const (
	errorReadHeader      = "Error reading header"
	errorSendHandshakeVM = "Error sending handshakeVM message"
	receivedHandshakeVM  = "Received a handshakeVM message"
	sentHandshakeVM      = "Sent a handshakeVM message"
	errorRunWorkerVM     = "Error run worker VM"
)

// TODO: подумать над тем как реагировать если сообщение пришло битое
func handleService(s Service) {
	h := s.GetPool().Get(TypeMsgHeader)
	e := h.Read(s.GetConn())
	if e != nil {
		s.GetLog().Error(errorReadHeader,
			zap.String("addr", s.GetAddr()),
			zap.Error(e),
		)
		return
	}

	switch h.GetType() {
	case TypeMsgHandshakeVM:
		msg := s.GetPool().Get(TypeMsgHandshakeVM)
		msg.SetHeader(h)
		s.GetLog().Info(receivedHandshakeVM,
			zap.String("addr", s.GetAddr()),
		)

		// Register messages VM
		s.SetCode(ServiceTypeVM)
		s.SetConfig(s.GetMaster().GetConfig().(*Config).ServiceVM)
		s.SetPool(NewPoolMessages(ServiceTypeVM))

		var n uint32
		for n < msg.GetLen() {
			if e = s.RunNewSlave(); e != nil {
				s.GetLog().Error(errorRunWorkerVM,
					zap.String("addr", s.GetAddr()),
					zap.Int("type", s.GetCode()),
					zap.Error(e),
				)
			}
			n--
		}

		// prepare ports for msg
		ports := make([]uint32, 0, s.GetSlaves().Len())
		addrs := s.GetSlaves().GetKeys()
		for i := range addrs {
			ports = append(ports, ExtractPort(addrs[i]))
		}
		msg.(*Handshake).Ports = ports
		msg.SetLen(uint32(len(ports) * 4))

		if e = msg.Write(s.GetConn()); e != nil {
			s.GetLog().Error(errorSendHandshakeVM,
				zap.String("addr", s.GetAddr()),
				zap.Int("type", s.GetCode()),
				zap.Error(e),
			)
			return
		}
		s.GetLog().Info(sentHandshakeVM,
			zap.String("addr", s.GetAddr()),
			zap.Int("type", s.GetCode()),
			zap.Error(e),
		)
	case TypeMsgGameNotification:
		// TODO: handleGameNotification(srv)
	case TypeMsgHandshakeASM:
		// TODO: handleHandshakeASM(srv)
	}
}
