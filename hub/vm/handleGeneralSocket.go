package main

import (
	"fmt"
	"net"
)

func handleGeneralSocket(conn net.Conn) error {
	var (
		addr = conn.RemoteAddr().String()
		typeMsg uint8
		err error
	)

	typeMsg, err = readTypeMsg(conn)
	if err != nil {
		return fmt.Errorf("Error reading type msg: %v ", err)
	}

	switch typeMsg {
	case TypeMsgHandshakeVM:
		fmt.Printf("Conn %v: Handling handshakeVM...\n", addr)
		if err = handleHandshakeVM(conn); err != nil {
			return fmt.Errorf("Error handle handshakeVM message: %v ", err)
		}
	case TypeMsgGameNotification:
		fmt.Printf("Conn %v: Handling game notification...\n", addr)
		if err = handleGameNotification(conn); err != nil {
			return fmt.Errorf("Error handle game notification message: %v ", err)
		}
	case TypeMsgHandshakeASM:
		fmt.Printf("Conn %v: Handling handshakeASM...\n", addr)
		if err = handleHandshakeASM(conn); err != nil {
			return fmt.Errorf("Error handle handshakeASM message: %v ", err)
		}
	}

	return err
}
