package main

import (
	"encoding/binary"
	"io"
)

type Handshake struct {
	Header
	Ports []uint32
	buff  *BufferMessage
}

func NewHandshake(buff *BufferMessage) *Handshake {
	return &Handshake{
		Header: *NewHeader(NewBufferMessage(sizeHeader)),
		buff:   buff,
	}
}

func (m *Handshake) SetHeader(h *Header) {
	m.Header.SetHeader(h)
}

func (m *Handshake) Read(r io.Reader) (e error) {
	m.buff.Reset()
	if e = m.buff.ReadN(r, int(m.Len)); e != nil {
		return e
	}

	if cap(m.Ports) < int(m.Len) {
		m.Ports = make([]uint32, 0, m.Len)
	}
	m.Ports = m.Ports[len(m.Ports):]

	var k, port uint32
	for k < m.Len {
		if e = binary.Read(m.buff, binary.BigEndian, &port); e != nil {
			break
		}
		m.Ports = append(m.Ports, port)
		k += 4
	}
	return e
}

func (m *Handshake) Write(w io.Writer) (e error) {
	m.buff.Reset()
	if e = m.Header.Write(m.buff); e != nil {
		return e
	}
	for _, port := range m.Ports {
		if e = binary.Write(m.buff, binary.BigEndian, &port); e != nil {
			return e
		}
	}
	return m.buff.WriteN(w, m.buff.Len())
}

//func sendHandshakeVM(conn *net.TCPConn, vm *HandshakeVM) error {
//	var (
//		err     error
//		i, port uint32
//		ports   = make([]uint32, 0, vm.NumWorkers)
//	)
//
//	ctx, interrupt := context.WithCancel(context.Background())
//	for i = 0; i < vm.NumWorkers; i++ {
//		port, err = launchWorkers(ctx)
//		if err != nil {
//			interrupt()
//			return fmt.Errorf("Error launching worker: %v ", err)
//		}
//		ports = append(ports, port)
//	}
//
//	msg := Handshake2VM{
//		Type:  TypeMsgHandshakeHB,
//		Key:   vm.Key,
//		Ports: ports,
//	}
//
//	return msg.Send(conn)
//}
