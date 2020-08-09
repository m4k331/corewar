package main

import (
	"encoding/binary"
	"io"
)

const (
	GameStatusPayloadSize = 8209
	ArenaSize             = 4096
)

type GameStatus struct {
	Header
	CyclesOfDeath    uint32
	CyclesDone       uint32
	NumberOfLivesOps uint32
	NumberOfChecks   uint32
	LastLivedPlayer  uint8
	Arena            [ArenaSize]byte
	Setting          [ArenaSize]byte
	buff             *BufferMessage
}

func NewGameStatus(buff *BufferMessage) *GameStatus {
	return &GameStatus{
		Header: *NewHeader(NewBufferMessage(sizeHeader)),
		buff:   buff,
	}
}

func (m *GameStatus) Read(r io.Reader) (e error) {
	m.buff.Reset()
	if e = m.buff.ReadN(r, int(m.Len)); e != nil {
		return e
	}
	if e = binary.Read(m.buff, binary.BigEndian, &m.CyclesOfDeath); e != nil {
		return e
	}
	if e = binary.Read(m.buff, binary.BigEndian, &m.CyclesDone); e != nil {
		return e
	}
	if e = binary.Read(m.buff, binary.BigEndian, &m.NumberOfLivesOps); e != nil {
		return e
	}
	if e = binary.Read(m.buff, binary.BigEndian, &m.NumberOfChecks); e != nil {
		return e
	}
	if e = binary.Read(m.buff, binary.BigEndian, &m.LastLivedPlayer); e != nil {
		return e
	}
	if _, e = m.buff.Read(m.Arena[:]); e != nil {
		return e
	}
	_, e = m.buff.Read(m.Setting[:])
	return e
}

func (m *GameStatus) Write(w io.Writer) (e error) {
	m.buff.Reset()
	if e = m.Header.Write(m.buff); e != nil {
		return e
	}
	if e = binary.Write(m.buff, binary.BigEndian, &m.CyclesOfDeath); e != nil {
		return e
	}
	if e = binary.Write(m.buff, binary.BigEndian, &m.CyclesDone); e != nil {
		return e
	}
	if e = binary.Write(m.buff, binary.BigEndian, &m.NumberOfLivesOps); e != nil {
		return e
	}
	if e = binary.Write(m.buff, binary.BigEndian, &m.NumberOfChecks); e != nil {
		return e
	}
	if e = binary.Write(m.buff, binary.BigEndian, &m.LastLivedPlayer); e != nil {
		return e
	}
	if _, e = m.buff.Write(m.Arena[:]); e != nil {
		return e
	}
	if _, e = m.buff.Write(m.Setting[:]); e != nil {
		return e
	}
	return m.buff.WriteN(w, m.buff.Len())
}

func (m *GameStatus) SetHeader(h Message) {
	m.Header.SetHeader(h)
}

func (m *GameStatus) GetType() uint8 {
	return m.Type
}

func (m *GameStatus) GetKey() uint32 {
	return m.Key
}

func (m *GameStatus) GetLen() uint32 {
	return m.Len
}

func (m *GameStatus) SetType(v uint8) {
	m.Type = v
}

func (m *GameStatus) SetKey(v uint32) {
	m.Key = v
}

func (m *GameStatus) SetLen(v uint32) {
	m.Len = v
}
