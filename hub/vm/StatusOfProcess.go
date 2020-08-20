package main

import (
	"io"
)

type StatusOfProcess struct {
	Header
	Message []byte
	buff    *BufferMessage
}

func NewStatusOfProcess(buff *BufferMessage) *StatusOfProcess {
	return &StatusOfProcess{
		Header: *NewHeader(NewBufferMessage(sizeHeader)),
		buff:   buff,
	}
}

func (m *StatusOfProcess) Read(r io.Reader) (e error) {
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

func (m *StatusOfProcess) Write(w io.Writer) (e error) {
	m.buff.Reset()
	if e = m.Header.Write(m.buff); e != nil {
		return e
	}
	if _, e = m.buff.Write(m.Message); e != nil {
		return e
	}
	return m.buff.WriteN(w, m.buff.Len())
}

func (m *StatusOfProcess) SetHeader(h Message) {
	m.Header.SetHeader(h)
}

func (m *StatusOfProcess) GetType() uint8 {
	return m.Type
}

func (m *StatusOfProcess) GetKey() uint32 {
	return m.Key
}

func (m *StatusOfProcess) GetLen() uint32 {
	return m.Len
}

func (m *StatusOfProcess) SetType(v uint8) {
	m.Type = v
}

func (m *StatusOfProcess) SetKey(v uint32) {
	m.Key = v
}

func (m *StatusOfProcess) SetLen(v uint32) {
	m.Len = v
}
