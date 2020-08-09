package main

import (
	"encoding/binary"
	"io"
)

const sizeHeader = 9

type Header struct {
	Type uint8
	Key  uint32
	Len  uint32
	buff *BufferMessage
}

func NewHeader(buff *BufferMessage) *Header {
	return &Header{buff: buff}
}

func (m *Header) Read(r io.Reader) (e error) {
	m.buff.Reset()
	if e = m.buff.ReadN(r, sizeHeader); e != nil {
		return e
	}
	if e = binary.Read(m.buff, binary.BigEndian, &m.Type); e != nil {
		return e
	}
	if e = binary.Read(m.buff, binary.BigEndian, &m.Key); e != nil {
		return e
	}
	return binary.Read(m.buff, binary.BigEndian, &m.Len)
}

func (m *Header) Write(w io.Writer) (e error) {
	m.buff.Reset()
	if e = binary.Write(m.buff, binary.BigEndian, &m.Type); e != nil {
		return e
	}
	if e = binary.Write(m.buff, binary.BigEndian, &m.Key); e != nil {
		return e
	}
	if e = binary.Write(m.buff, binary.BigEndian, &m.Len); e != nil {
		return e
	}
	return m.buff.WriteN(w, sizeHeader)
}

func (m *Header) SetHeader(h Message) {
	m.Type = h.GetType()
	m.Key = h.GetKey()
	m.Len = h.GetLen()
}

func (m *Header) GetType() uint8 {
	return m.Type
}

func (m *Header) GetKey() uint32 {
	return m.Key
}

func (m *Header) GetLen() uint32 {
	return m.Len
}
