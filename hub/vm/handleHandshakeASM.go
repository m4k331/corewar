package main

import (
	"bytes"
	"context"
	"encoding/binary"
	"fmt"
	"net"
)

func handleHandshakeASM(conn net.Conn) error {
	var (
		err  error
		msg  *HandshakeASM
		addr = conn.RemoteAddr().String()
	)

	msg, err = readHandshakeASM(conn)
	if err != nil {
		return fmt.Errorf("Error reading msg: %v ", err)
	}
	fmt.Printf("Hub received a handshakeASM msg from %s\n", addr)

	// TODO: need asm manager
	ctx, _ := context.WithCancel(context.Background())
	m := make(chan *BotASM, 10)
	go handleIncomingASM(ctx, conn)
	go handleOutgoingASM(ctx, conn, m)
	err = msg.Send(conn)
	if err != nil {
		return fmt.Errorf("Error sending handshake ASM: %v\n", err)
	}
	fmt.Printf("Hub Write handshake ASM to %s\n", addr)

	return err
}
