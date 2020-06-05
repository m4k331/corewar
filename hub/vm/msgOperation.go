package main

import (
	"encoding/binary"
	"fmt"
	"net"
)

type Operation struct {
	Type uint8
	Id uint32
	Len uint32
	ProcId uint32
	ProcPos uint16
	Message []byte
}

func readOperation(conn net.Conn) (*Operation, error) {
	var (
		n int
		e error
		m = new(Operation)
	)

	m.Type = TypeMsgOperation
	if e = binary.Read(conn, binary.BigEndian, &m.Id); e != nil {
		return m, e
	}
	if e = binary.Read(conn, binary.BigEndian, &m.Len); e != nil {
		return m, e
	}
	if e = binary.Read(conn, binary.BigEndian, &m.ProcId); e != nil {
		return m, e
	}
	if e = binary.Read(conn, binary.BigEndian, &m.ProcPos); e != nil {
		return m, e
	}
	m.Message = make([]byte, m.Len)
	if n, e = conn.Read(m.Message); n != int(m.Len) || e != nil {
		return m, fmt.Errorf("Error reading Message field (%d/%d): %v ", n, m.Len, e)
	}

	return m, e
}

func handleOperation(conn net.Conn) error {
	var (
		err error
		msg *Operation
		addr = conn.RemoteAddr().String()
	)

	msg, err = readOperation(conn)
	if err != nil  {
		return fmt.Errorf("Error reading msg: %v ", err)
	}
	fmt.Printf("Hub received an operation msg from %s\n", addr)

	// TODO: send operation on web site
	fmt.Printf("Hub send operation on web site " +
		"{id: %d, len: %d, procId: %d, procPos: %d}\n",
		msg.Id, msg.Len, msg.ProcId, msg.ProcPos)

	return err
}
