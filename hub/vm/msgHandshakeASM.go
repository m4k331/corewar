package main

import (
	"bytes"
	"context"
	"encoding/binary"
	"fmt"
	"net"
)

type HandshakeASM struct {
	Type uint8
	Key uint32
}

func (hba *HandshakeASM) Send(conn net.Conn) error {
	var (
		err error
		buf = new(bytes.Buffer)
	)

	if err = binary.Write(buf, binary.BigEndian, hba.Type); err != nil {
		return err
	}
	if err = binary.Write(buf, binary.BigEndian, hba.Key); err != nil {
		return err
	}
	if _, err = conn.Write(buf.Bytes()); err != nil {
		return err
	}
	return err
}

func readHandshakeASM(conn net.Conn) (*HandshakeASM, error) {
	var (
		e error
		m = new(HandshakeASM)
	)

	m.Type = TypeMsgHandshakeASM
	e = binary.Read(conn, binary.BigEndian, &m.Key)
	return m, e
}

func handleHandshakeASM(conn net.Conn) error {
	var (
		err error
		msg *HandshakeASM
		addr = conn.RemoteAddr().String()
	)

	msg, err = readHandshakeASM(conn)
	if err != nil {
		return fmt.Errorf("Error reading msg: %v ", err)
	}
	fmt.Printf("Hub received a handshakeASM msg from %s\n", addr)

	// TODO: need asm manager
	ctx, _ := context.WithCancel(context.Background())
	go handleASMWorker(ctx, conn)
	err = msg.Send(conn)
	if err != nil {
		return fmt.Errorf("Error sending handshake ASM: %v\n", err)
	}
	fmt.Printf("Hub send handshake ASM to %s\n", addr)

	return err
}
