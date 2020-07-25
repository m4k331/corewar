package main

import (
	"encoding/binary"
	"fmt"
	"net"
)

type GamePresentation struct {
	Type    uint8
	Id      uint32
	Len     uint32
	Comment []byte
}

func readGamePresentation(conn net.Conn) (*GamePresentation, error) {
	var (
		e error
		m = new(GamePresentation)
	)

	m.Type = TypeMsgGamePresentation
	if e = binary.Read(conn, binary.BigEndian, &m.Id); e != nil {
		return m, e
	}
	if e = binary.Read(conn, binary.BigEndian, &m.Len); e != nil {
		return m, e
	}
	m.Comment = make([]byte, m.Len)
	conn.Read(m.Comment)
	return m, e
}

func handleGamePresentation(conn net.Conn) error {
	var (
		err  error
		msg  *GamePresentation
		addr = conn.RemoteAddr().String()
	)

	msg, err = readGamePresentation(conn)
	if err != nil {
		return fmt.Errorf("Error reading msg: %v ", err)
	}
	fmt.Printf("Hub received a game presentation msg from %s\n", addr)

	// TODO: Write game notification on web site
	fmt.Printf("Hub Write game presentation on web site "+
		"{type: %d, id: %d, len: %d, msg: %s}\n",
		msg.Type, msg.Id, msg.Len, string(msg.Comment))

	return err
}
