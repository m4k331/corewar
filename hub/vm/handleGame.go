package main

import (
	"go.uber.org/zap"
)

func handleGame(s Service) {
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
	case TypeMsgGameStatus:
		// TODO: handler GameStatus
	case TypeMsgOperation:
		// TODO: handler Operation
	case TypeMsgStatusOfProcess:
		// TODO: handler StatusOfProcess
	case TypeMsgEndOfGame:
		// TODO: handler EndOfGame
	case TypeMsgGamePresentation:
		// TODO: handler GamePresentation
	}
}
