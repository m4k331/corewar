package main

import (
	"encoding/binary"
	"fmt"
	"net"
)

type BinaryASM struct {
	Type uint8
	Id   uint32
	Len  uint32
	Bot  []byte
}

func readBinaryASM(conn net.Conn) (*BinaryASM, error) {
	var (
		n int
		e error
		m = new(BinaryASM)
	)

	m.Type = TypeMsgBinaryASM
	if e = binary.Read(conn, binary.BigEndian, &m.Id); e != nil {
		return m, e
	}
	if e = binary.Read(conn, binary.BigEndian, &m.Len); e != nil {
		return m, e
	}
	m.Bot = make([]byte, m.Len)
	if n, e = conn.Read(m.Bot); n != int(m.Len) || e != nil {
		return m, fmt.Errorf("Error reading Message field (%d/%d): %v ", n, m.Len, e)
	}

	return m, e
}

func handleBinaryASM(conn net.Conn) error {
	var (
		err error
		msg *BinaryASM
		addr = conn.RemoteAddr().String()
	)

	msg, err = readBinaryASM(conn)
	if err != nil  {
		return fmt.Errorf("Error reading msg: %v ", err)
	}
	fmt.Printf("Hub received Binary ASM msg from %s\n", addr)

	// TODO: send Binary ASM on web site
	fmt.Printf("Hub send Binary ASM on web site " +
		"{id: %d, len: %d, bot: [%v]}\n",
		msg.Id, msg.Len, string(msg.Bot))

	return err
}
