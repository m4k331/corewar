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

func (m *Header) SetHeader(h *Header) {
	m.Type = h.Type
	m.Key = h.Key
	m.Len = h.Len
}
