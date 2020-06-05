package main

import (
	"encoding/binary"
	"fmt"
	"net"
)

const (
	commentSize = 2048
)

type GameNotification struct {
	Type uint8
	Id   uint32
	Len  uint32
	Socket  uint32
	Comment []byte
}

func readGameNotification(conn net.Conn) (*GameNotification, error) {
	var (
		e error
		m = new(GameNotification)
	)

	m.Type = TypeMsgGameNotification
	if e = binary.Read(conn, binary.BigEndian, &m.Id); e != nil {
		return m, e
	}
	if e = binary.Read(conn, binary.BigEndian, &m.Len); e != nil {
		return m, e
	}
	if e = binary.Read(conn, binary.BigEndian, &m.Socket); e != nil {
		return m, e
	}
	m.Len -= 4
	// TODO: check socket exist
	if m.Len % commentSize != 0 {
		return m, fmt.Errorf("Bad comment length %d ", m.Len)
	}
	m.Comment = make([]byte, m.Len)
	conn.Read(m.Comment)
	return m, e
}

func handleGameNotification(conn net.Conn) error {
	var (
		err error
		msg *GameNotification
		addr = conn.RemoteAddr().String()
	)

	msg, err = readGameNotification(conn)
	if err != nil {
		return fmt.Errorf("Error reading msg: %v ", err)
	}
	fmt.Printf("Hub received a game notification msg from %s\n", addr)

	// TODO: send game notification on web site
	fmt.Printf("Hub send game notification on web site {type: %d, id: %d, len: %d, socket: %d, msg: %d}\n", msg.Type, msg.Id, msg.Len, msg.Socket, len(msg.Comment))

	return err
}