package main

import (
	"context"
	"fmt"
	"net"
)

func handleOutgoingASM(ctx context.Context, conn net.Conn, m <-chan *BotASM) {
	var (
		addr = conn.RemoteAddr().String()
		msg  *BotASM
		err  error
	)

	for {
		select {
		case <-ctx.Done():
			fmt.Printf("Disconnect ASM outgoing worker %s\n", addr)
			return
		default:
			msg = <-m
			if err = msg.Send(conn); err != nil {
				fmt.Printf("Error conn %v sending bot source code %v\n", addr, err)
			}
		}
	}
}

func handleIncomingASM(ctx context.Context, conn net.Conn) {
	var (
		addr    = conn.RemoteAddr().String()
		typeMsg uint8
		err     error
	)

	for {
		select {
		case <-ctx.Done():
			fmt.Printf("Disconnect ASM incoming worker %s\n", addr)
			return
		default:
			typeMsg, err = ReadTypeMsg(conn)
			if err != nil {
				fmt.Printf("Error reading type msg in ASM worker (%v) : %v ", addr, err)
			}
			switch typeMsg {
			case TypeMsgErrorASM:
				fmt.Printf("Conn %v: Handling error ASM...\n", addr)
				if err = handleErrorASM(conn); err != nil {
					fmt.Printf("Error handle error ASM message: %v ", err)
				}
			case TypeMsgBotASM:
				fmt.Printf("Conn %v: Handling binary ASM...\n", addr)
				if err = handleBinaryASM(conn); err != nil {
					fmt.Printf("Error handle binary ASM message: %v ", err)
				}
			}
		}
	}
}
