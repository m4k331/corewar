package main

import (
	"encoding/binary"
	"io"
)

type EndOfGame struct {
	Header
	Winner  uint8
	Message []byte
	buff    *BufferMessage
}

func NewEndOfGame(buff *BufferMessage) *EndOfGame {
	return &EndOfGame{
		Header: *NewHeader(NewBufferMessage(sizeHeader)),
		buff:   buff,
	}
}

func (m *EndOfGame) Read(r io.Reader) (e error) {
	m.buff.Reset()
	if e = m.buff.ReadN(r, int(m.Len)); e != nil {
		return e
	}
	if e = binary.Read(m.buff, binary.BigEndian, &m.Winner); e != nil {
		return e
	}

	if cap(m.Message) < m.buff.Len() {
		m.Message = make([]byte, m.buff.Len())
	}

	_, e = m.buff.Read(m.Message[:m.buff.Len()])
	return e
}

func (m *EndOfGame) Write(w io.Writer) (e error) {
	m.buff.Reset()
	if e = m.Header.Write(m.buff); e != nil {
		return e
	}
	if e = binary.Write(m.buff, binary.BigEndian, &m.Winner); e != nil {
		return e
	}
	if _, e = m.buff.Write(m.Message); e != nil {
		return e
	}
	return m.buff.WriteN(w, m.buff.Len())
}

func (m *EndOfGame) SetHeader(h Message) {
	m.Header.SetHeader(h)
}

func (m *EndOfGame) GetType() uint8 {
	return m.Type
}

func (m *EndOfGame) GetKey() uint32 {
	return m.Key
}

func (m *EndOfGame) GetLen() uint32 {
	return m.Len
}
