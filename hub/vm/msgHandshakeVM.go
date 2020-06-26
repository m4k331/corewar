package main

import (
	"encoding/binary"
	"fmt"
	"net"
)

const MaxNumWorkers = 24

type HandshakeVM struct {
	Type       uint8
	Key        uint32
	NumWorkers uint32
}

func readHandshakeVM(conn net.Conn) (*HandshakeVM, error) {
	var (
		e error
		m = new(HandshakeVM)
	)

	m.Type = TypeMsgHandshakeVM
	if e = binary.Read(conn, binary.BigEndian, &m.Key); e != nil {
		return m, e
	}
	if e = binary.Read(conn, binary.BigEndian, &m.NumWorkers); e != nil {
		return m, e
	}
	if m.NumWorkers > MaxNumWorkers {
		return m, fmt.Errorf("Maximum number of workers exceeded (%d/%d) ", m.NumWorkers, MaxNumWorkers)
	}
	return m, e
}

func handleHandshakeVM(conn net.Conn) error {
	var (
		err  error
		msg  *HandshakeVM
		addr = conn.RemoteAddr().String()
	)

	msg, err = readHandshakeVM(conn)
	if err != nil {
		return fmt.Errorf("Error reading msg: %v ", err)
	}
	fmt.Printf("Hub received a handshakeVM msg from %s\n", addr)

	err = sendHandshake2VM(conn, msg)
	if err != nil {
		return fmt.Errorf("Error sending handshake: %v\n", err)
	}
	fmt.Printf("Hub send handshake to %s\n", addr)

	return err
}
