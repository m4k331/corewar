package main

import "io"

const (
	TypeMsgHandshakeVM = iota + 1
	_
	TypeMsgGameNotification
	TypeMsgGameStatus
	TypeMsgOperation
	TypeMsgStatusOfProcess
	TypeMsgEndOfGame
	TypeMsgGamePresentation
)

const (
	TypeMsgHandshakeHB = iota + 1
	TypeMsgInitialGame
	TypeMsgSendBot
)

const (
	TypeMsgHandshakeASM = iota + 101
	TypeMsgErrorASM
	TypeMsgBinaryASM
)

type Message interface {
	SetHeader(h *Header)
	Read(r io.Reader) error
	Write(w io.Writer) error
}
