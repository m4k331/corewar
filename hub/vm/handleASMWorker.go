package main

import (
	"context"
	"fmt"
	"net"
)

func handleASMWorker(ctx context.Context, conn net.Conn) {
	var (
		addr    = conn.RemoteAddr().String()
		typeMsg uint8
		err     error
	)

	for {
		select {
		case <-ctx.Done():
			fmt.Printf("Disconnect ASM worker %s\n", addr)
			return
		default:
			typeMsg, err = readTypeMsg(conn)
			if err != nil {
				fmt.Printf("Error reading type msg in ASM worker (%v) : %v ", addr, err)
			}
			switch typeMsg {
			case TypeMsgErrorASM:
				fmt.Printf("Conn %v: Handling error ASM...\n", addr)
				if err = handleErrorASM(conn); err != nil {
					fmt.Printf("Error handle error ASM message: %v ", err)
				}
			case TypeMsgBinaryASM:
				fmt.Printf("Conn %v: Handling binary ASM...\n", addr)
				if err = handleBinaryASM(conn); err != nil {
					fmt.Printf("Error handle binary ASM message: %v ", err)
				}
			}
		}
	}
}
