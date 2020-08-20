package main

import (
	"io"
)

type ErrorASM struct {
	Header
	Message []byte
	buff    *BufferMessage
}

func NewErrorASM(buff *BufferMessage) *ErrorASM {
	return &ErrorASM{
		Header: *NewHeader(NewBufferMessage(sizeHeader)),
		buff:   buff,
	}
}

func (m *ErrorASM) Read(r io.Reader) (e error) {
	m.buff.Reset()
	if e = m.buff.ReadN(r, int(m.Len)); e != nil {
		return e
	}

	if cap(m.Message) < int(m.Len) {
		m.Message = make([]byte, m.Len)
	}

	_, e = m.buff.Read(m.Message[:m.Len])
	return e
}

func (m *ErrorASM) Write(w io.Writer) (e error) {
	m.buff.Reset()
	if e = m.Header.Write(m.buff); e != nil {
		return e
	}
	if _, e = m.buff.Write(m.Message); e != nil {
		return e
	}
	return m.buff.WriteN(w, m.buff.Len())
}

func (m *ErrorASM) SetHeader(h Message) {
	m.Header.SetHeader(h)
}

func (m *ErrorASM) GetType() uint8 {
	return m.Type
}

func (m *ErrorASM) GetKey() uint32 {
	return m.Key
}

func (m *ErrorASM) GetLen() uint32 {
	return m.Len
}

func (m *ErrorASM) SetType(v uint8) {
	m.Type = v
}

func (m *ErrorASM) SetKey(v uint32) {
	m.Key = v
}

func (m *ErrorASM) SetLen(v uint32) {
	m.Len = v
}
