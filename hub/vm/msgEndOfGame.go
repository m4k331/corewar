package main

import (
	"encoding/binary"
	"fmt"
	"net"
)

type EndOfGame struct {
	Type    uint8
	Id      uint32
	Len     uint32
	Winner  uint8
	Message []byte
}

func readEndOfGame(conn net.Conn) (*EndOfGame, error) {
	var (
		n int
		e error
		m = new(EndOfGame)
	)

	m.Type = TypeMsgEndOfGame
	if e = binary.Read(conn, binary.BigEndian, &m.Id); e != nil {
		return m, e
	}
	if e = binary.Read(conn, binary.BigEndian, &m.Len); e != nil {
		return m, e
	}
	if e = binary.Read(conn, binary.BigEndian, &m.Winner); e != nil {
		return m, e
	}
	m.Message = make([]byte, m.Len)
	if n, e = conn.Read(m.Message); n != int(m.Len) || e != nil {
		return m, fmt.Errorf("Error reading Message field (%d/%d): %v ", n, m.Len, e)
	}

	return m, e
}

func handleEndOfGame(conn net.Conn) error {
	var (
		err  error
		msg  *EndOfGame
		addr = conn.RemoteAddr().String()
	)

	msg, err = readEndOfGame(conn)
	if err != nil {
		return fmt.Errorf("Error reading msg: %v ", err)
	}
	fmt.Printf("Hub received an end of game msg from %s\n", addr)

	// TODO: send end of game on web site
	fmt.Printf("Hub send end of game on web site "+
		"{id: %d, len: %d, winner: %d}\n",
		msg.Id, msg.Len, msg.Winner)

	return err
}
