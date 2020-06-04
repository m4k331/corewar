package main

import (
	"encoding/binary"
	"fmt"
	"golang.org/x/net/context"
	"net"
)

type Handshake2VM struct {
	Type  uint8
	Key   uint32
	Ports []uint32
}

func (hb *Handshake2VM) Send(conn net.Conn) error {
	var err error

	if err = binary.Write(conn, binary.BigEndian, &hb.Type); err != nil {
		return err
	}
	if err = binary.Write(conn, binary.BigEndian, &hb.Key); err != nil {
		return err
	}
	for i := range hb.Ports {
		if err = binary.Write(conn, binary.BigEndian, &hb.Ports[i]); err != nil {
			return err
		}
	}
	return err
}

func launchWorkers(ctx context.Context) (uint32, error) {
	listener, err := net.Listen("tcp", ":0")
	if err != nil {
		return 0, err
	}
	
	addr := listener.Addr().String()
	fmt.Printf("Launch new listener for worker %s\n", addr)
	
	go func() {
		defer func() {
			err = listener.Close()
			fmt.Printf("Listener %s closed %v\n", addr, err)
		}()
		chanConn := make(chan net.Conn)
		go func() {
			for {
				accept, err := listener.Accept()
				if err != nil {
					fmt.Printf("Listener %s fail accept :c\n", addr)
					continue
				}
				chanConn <- accept
				break
			}
		}()
		select {
		case conn := <-chanConn:
			fmt.Printf("Accept worker conn %v\n", conn.RemoteAddr().String())
			go handleConnection(conn, handleGameWorker)
		case <-ctx.Done():
			break
		}
	}()

	return portFromAddress(addr), err
}

func sendHandshake2VM(conn net.Conn, vm *HandshakeVM) error {
	var (
		err     error
		i, port uint32
		ports = make([]uint32, 0, vm.NumWorkers)
	)

	ctx, interrupt := context.WithCancel(context.Background())
	for i = 0; i < vm.NumWorkers; i++ {
		port, err = launchWorkers(ctx)
		if err != nil {
			interrupt()
			return fmt.Errorf("Error launching worker: %v ", err)
		}
		ports = append(ports, port)
	}

	msg := Handshake2VM{
		Type:  TypeMsgHandshakeHB,
		Key:   vm.Key,
		Ports: ports,
	}

	return msg.Send(conn)
}
