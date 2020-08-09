package main

import (
	"encoding/binary"
	"io"
)

type InitialGame struct {
	Header
	Number uint8
	Champs []byte
	buff   *BufferMessage
}

func NewInitialGame(buff *BufferMessage) *InitialGame {
	return &InitialGame{
		Header: *NewHeader(NewBufferMessage(sizeHeader)),
		buff:   buff,
	}
}

func (m *InitialGame) Read(r io.Reader) (e error) {
	m.buff.Reset()
	if e = m.buff.ReadN(r, int(m.Len)); e != nil {
		return e
	}
	if e = binary.Read(m.buff, binary.BigEndian, &m.Number); e != nil {
		return e
	}

	if cap(m.Champs) < m.buff.Len() {
		m.Champs = make([]byte, m.buff.Len())
	}

	_, e = m.buff.Read(m.Champs[:m.buff.Len()])
	return e
}

func (m *InitialGame) Write(w io.Writer) (e error) {
	m.buff.Reset()
	if e = m.Header.Write(m.buff); e != nil {
		return e
	}
	if e = binary.Write(m.buff, binary.BigEndian, &m.Number); e != nil {
		return e
	}
	if _, e = m.buff.Write(m.Champs); e != nil {
		return e
	}
	return m.buff.WriteN(w, m.buff.Len())
}

func (m *InitialGame) SetHeader(h Message) {
	m.Header.SetHeader(h)
}

func (m *InitialGame) GetType() uint8 {
	return m.Type
}

func (m *InitialGame) GetKey() uint32 {
	return m.Key
}

func (m *InitialGame) GetLen() uint32 {
	return m.Len
}
