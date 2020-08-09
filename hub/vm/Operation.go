package main

import (
	"encoding/binary"
	"io"
)

type Operation struct {
	Header
	ProcId  uint32
	ProcPos uint16
	Message []byte
	buff    *BufferMessage
}

func NewOperation(buff *BufferMessage) *Operation {
	return &Operation{
		Header: *NewHeader(NewBufferMessage(sizeHeader)),
		buff:   buff,
	}
}

func (m *Operation) SetHeader(h *Header) {
	m.Header.SetHeader(h)
}

func (m *Operation) Read(r io.Reader) (e error) {
	m.buff.Reset()
	if e = m.buff.ReadN(r, int(m.Len)); e != nil {
		return e
	}
	if e = binary.Read(m.buff, binary.BigEndian, &m.ProcId); e != nil {
		return e
	}
	if e = binary.Read(m.buff, binary.BigEndian, &m.ProcPos); e != nil {
		return e
	}

	if cap(m.Message) < m.buff.Len() {
		m.Message = make([]byte, m.buff.Len())
	}

	_, e = m.buff.Read(m.Message[:m.buff.Len()])
	return e
}

func (m *Operation) Write(w io.Writer) (e error) {
	m.buff.Reset()
	if e = m.Header.Write(m.buff); e != nil {
		return e
	}
	if e = binary.Write(m.buff, binary.BigEndian, &m.ProcId); e != nil {
		return e
	}
	if e = binary.Write(m.buff, binary.BigEndian, &m.ProcPos); e != nil {
		return e
	}
	if _, e = m.buff.Write(m.Message); e != nil {
		return e
	}
	return m.buff.WriteN(w, m.buff.Len())
}
