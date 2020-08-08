package main

import (
	"encoding/binary"
	"errors"
	"io"
)

type GameNotification struct {
	Header
	Socket uint32
	buff   *BufferMessage
}

func NewGameNotification(buff *BufferMessage) *GameNotification {
	return &GameNotification{
		Header: *NewHeader(NewBufferMessage(sizeHeader)),
		buff:   buff,
	}
}

func (m *GameNotification) SetHeader(h *Header) {
	m.Header.SetHeader(h)
}

func (m *GameNotification) Read(r io.Reader) (e error) {
	if m.Len != 4 {
		return errors.New("bad payload size")
	}
	return binary.Read(r, binary.BigEndian, &m.Socket)
}

func (m *GameNotification) Write(w io.Writer) (e error) {
	m.buff.Reset()
	if e = m.Header.Write(m.buff); e != nil {
		return e
	}
	if e = binary.Write(m.buff, binary.BigEndian, &m.Socket); e != nil {
		return e
	}
	return m.buff.WriteN(w, m.buff.Len())
}
