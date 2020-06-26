package main

import (
	"encoding/binary"
	"fmt"
	"net"
)

type StatusOfProcess struct {
	Type    uint8
	Id      uint32
	Len     uint32
	Message []byte
}

func readStatusOfProcess(conn net.Conn) (*StatusOfProcess, error) {
	var (
		n int
		e error
		m = new(StatusOfProcess)
	)

	m.Type = TypeMsgStatusOfProcess
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

func handleStatusOfProcess(conn net.Conn) error {
	var (
		err  error
		msg  *StatusOfProcess
		addr = conn.RemoteAddr().String()
	)

	msg, err = readStatusOfProcess(conn)
	if err != nil {
		return fmt.Errorf("Error reading msg: %v ", err)
	}
	fmt.Printf("Hub received a status of process msg from %s\n", addr)

	// TODO: send status of process on web site
	fmt.Printf("Hub send status of process on web site "+
		"{id: %d, len: %d}\n",
		msg.Id, msg.Len)

	return err
}
