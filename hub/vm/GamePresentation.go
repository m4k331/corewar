package main

import "io"

type GamePresentation struct {
	Header
	Comment []byte
	buff    *BufferMessage
}

func NewGamePresentation(buff *BufferMessage) *GamePresentation {
	return &GamePresentation{
		Header: *NewHeader(NewBufferMessage(sizeHeader)),
		buff:   buff,
	}
}

func (m *GamePresentation) Read(r io.Reader) (e error) {
	m.buff.Reset()
	if e = m.buff.ReadN(r, int(m.Len)); e != nil {
		return e
	}

	if cap(m.Comment) < int(m.Len) {
		m.Comment = make([]byte, m.Len)
	}

	_, e = m.buff.Read(m.Comment[:m.Len])
	return e
}

func (m *GamePresentation) Write(w io.Writer) (e error) {
	m.buff.Reset()
	if e = m.Header.Write(m.buff); e != nil {
		return e
	}
	if _, e = m.buff.Write(m.Comment); e != nil {
		return e
	}
	return m.buff.WriteN(w, m.buff.Len())
}

func (m *GamePresentation) SetHeader(h Message) {
	m.Header.SetHeader(h)
}

func (m *GamePresentation) GetType() uint8 {
	return m.Type
}

func (m *GamePresentation) GetKey() uint32 {
	return m.Key
}

func (m *GamePresentation) GetLen() uint32 {
	return m.Len
}
