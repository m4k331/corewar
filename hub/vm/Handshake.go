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

func (m *Handshake) SetHeader(h Message) {
	m.Header.SetHeader(h)
}

func (m *Handshake) GetType() uint8 {
	return m.Type
}

func (m *Handshake) GetKey() uint32 {
	return m.Key
}

func (m *Handshake) GetLen() uint32 {
	return m.Len
}

func (m *Handshake) SetType(v uint8) {
	m.Type = v
}

func (m *Handshake) SetKey(v uint32) {
	m.Key = v
}

func (m *Handshake) SetLen(v uint32) {
	m.Len = v
}
