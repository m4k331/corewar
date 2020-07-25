package main

import (
	"bytes"
	"context"
	"encoding/binary"
	"fmt"
	"io"
	"net"
)

const MaxNumWorkers = 24

type HandshakeVM struct {
	Type       uint8
	Key        uint32
	NumWorkers uint32
	Ports      []uint32
}

func (m *HandshakeVM) Read(r io.Reader) (e error) {
	m.Type = TypeMsgHandshakeVM
	if e = binary.Read(r, binary.BigEndian, &m.Key); e != nil {
		return e
	}
	if e = binary.Read(r, binary.BigEndian, &m.NumWorkers); e != nil {
		return e
	}
	if m.NumWorkers > MaxNumWorkers {
		return fmt.Errorf("Maximum number of workers exceeded (%d/%d) ", m.NumWorkers, MaxNumWorkers)
	}
	return e
}

func (m *HandshakeVM) Write(w io.Writer) (e error) {
	buff := new(bytes.Buffer)
	if e = binary.Write(buff, binary.BigEndian, m.Type); e != nil {
		return e
	}
	if e = binary.Write(buff, binary.BigEndian, m.Key); e != nil {
		return e
	}
	for i := range m.Ports {
		if e = binary.Write(buff, binary.BigEndian, m.Ports[i]); e != nil {
			return e
		}
	}
	if _, e = w.Write(buff.Bytes()); e != nil {
		return e
	}
	return e
}

func launchWorkers(ctx context.Context) (uint32, error) {

}

func sendHandshakeVM(conn net.Conn, vm *HandshakeVM) error {
	var (
		err     error
		i, port uint32
		ports   = make([]uint32, 0, vm.NumWorkers)
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
