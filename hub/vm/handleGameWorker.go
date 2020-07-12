package main

import (
	"fmt"
	"net"
)

func handleGameWorker(conn net.Conn) error {
	var (
		addr    = conn.RemoteAddr().String()
		typeMsg uint8
		err     error
	)

	typeMsg, err = readTypeMsg(conn)
	fmt.Println("game worker", typeMsg, err)
	if err != nil {
		return fmt.Errorf("Error reading type msg: %v ", err)
	}

	switch typeMsg {
	case TypeMsgGameStatus:
		fmt.Printf("Worker %v: Handling game status...\n", addr)
		if err = handleGameStatus(conn); err != nil {
			return fmt.Errorf("Error handle game status message: %v ", err)
		}
	case TypeMsgOperation:
		fmt.Printf("Worker %v: Handling operation...\n", addr)
		if err = handleOperation(conn); err != nil {
			return fmt.Errorf("Error handle operation message: %v ", err)
		}
	case TypeMsgStatusOfProcess:
		fmt.Printf("Worker %v: Handling status of process...\n", addr)
		if err = handleStatusOfProcess(conn); err != nil {
			return fmt.Errorf("Error handle status of process message: %v ", err)
		}
	case TypeMsgEndOfGame:
		fmt.Printf("Worker %v: Handling end of game...\n", addr)
		if err = handleEndOfGame(conn); err != nil {
			return fmt.Errorf("Error handle end of game message: %v ", err)
		}
	case TypeMsgGamePresentation:
		fmt.Printf("Worker %v: Handling game presentation...\n", addr)
		if err = handleGamePresentation(conn); err != nil {
			return fmt.Errorf("Error handle game presentation message: %v ", err)
		}
	}

	return err
}
