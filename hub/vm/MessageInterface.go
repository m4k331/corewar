package main

import "io"

const (
	TypeMsgHeader = iota
	TypeMsgHandshakeVM
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
	TypeMsgBotASM
)

type Message interface {
	SetHeader(h *Header)
	Read(r io.Reader) error
	Write(w io.Writer) error
}
