package main

import "io"

type BotASM struct {
	Header
	Bot  []byte
	buff *BufferMessage
}

func NewBotASM(buff *BufferMessage) *BotASM {
	return &BotASM{
		Header: *NewHeader(NewBufferMessage(sizeHeader)),
		buff:   buff,
	}
}

func (m *BotASM) Read(r io.Reader) (e error) {
	m.buff.Reset()
	if e = m.buff.ReadN(r, int(m.Len)); e != nil {
		return e
	}

	if cap(m.Bot) < int(m.Len) {
		m.Bot = make([]byte, m.Len)
	}

	_, e = m.buff.Read(m.Bot[:m.Len])
	return e
}

func (m *BotASM) Write(w io.Writer) (e error) {
	m.buff.Reset()
	if e = m.Header.Write(m.buff); e != nil {
		return e
	}
	if _, e = m.buff.Write(m.Bot); e != nil {
		return e
	}
	return m.buff.WriteN(w, m.buff.Len())
}

func (m *BotASM) SetHeader(h Message) {
	m.Header.SetHeader(h)
}

func (m *BotASM) GetType() uint8 {
	return m.Type
}

func (m *BotASM) GetKey() uint32 {
	return m.Key
}

func (m *BotASM) GetLen() uint32 {
	return m.Len
}

func (m *BotASM) SetType(v uint8) {
	m.Type = v
}

func (m *BotASM) SetKey(v uint32) {
	m.Key = v
}

func (m *BotASM) SetLen(v uint32) {
	m.Len = v
}
