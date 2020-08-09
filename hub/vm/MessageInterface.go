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
)

const (
	TypeMsgHandshakeASM = iota + 101
	TypeMsgErrorASM
	TypeMsgBotASM
)

type Message interface {
	SetHeader(h Message)
	Read(r io.Reader) error
	Write(w io.Writer) error
	GetType() uint8
	GetKey() uint32
	GetLen() uint32
}
