package main

import (
	"encoding/binary"
	"fmt"
	"net"
)

type ErrorASM struct {
	Type    uint8
	Id      uint32
	Len     uint32
	Message []byte
}

func readErrorASM(conn net.Conn) (*ErrorASM, error) {
	var (
		n int
		e error
		m = new(ErrorASM)
	)

	m.Type = TypeMsgErrorASM
	if e = binary.Read(conn, binary.BigEndian, &m.Id); e != nil {
		return m, e
	}
	if e = binary.Read(conn, binary.BigEndian, &m.Len); e != nil {
		return m, e
	}
	m.Message = make([]byte, m.Len)
	if n, e = conn.Read(m.Message); n != int(m.Len) || e != nil {
		return m, fmt.Errorf("Error reading Message field (%d/%d): %v ", n, m.Len, e)
	}

	return m, e
}

func handleErrorASM(conn net.Conn) error {
	var (
		err error
		msg *ErrorASM
		addr = conn.RemoteAddr().String()
	)

	msg, err = readErrorASM(conn)
	if err != nil  {
		return fmt.Errorf("Error reading msg: %v ", err)
	}
	fmt.Printf("Hub received error ASM msg from %s\n", addr)

	// TODO: send error ASM on web site
	fmt.Printf("Hub send error ASM on web site " +
		"{id: %d, len: %d, msg: %v}\n",
		msg.Id, msg.Len, string(msg.Message))

	return err
}
