package main

import (
	"bytes"
	"encoding/binary"
	"reflect"
	"testing"
)

func genBinaryGameStatus(m *GameStatus) []byte {
	b := new(bytes.Buffer)
	_ = binary.Write(b, binary.BigEndian, &m.Type)
	_ = binary.Write(b, binary.BigEndian, &m.Key)
	_ = binary.Write(b, binary.BigEndian, &m.Len)
	_ = binary.Write(b, binary.BigEndian, &m.CyclesOfDeath)
	_ = binary.Write(b, binary.BigEndian, &m.CyclesDone)
	_ = binary.Write(b, binary.BigEndian, &m.NumberOfLivesOps)
	_ = binary.Write(b, binary.BigEndian, &m.NumberOfChecks)
	_ = binary.Write(b, binary.BigEndian, &m.LastLivedPlayer)
	b.Write(m.Arena[:])
	b.Write(m.Setting[:])
	return b.Bytes()
}

func TestGameStatus(t *testing.T) {
	m := &GameStatus{
		Header: Header{
			Type: 1,
			Key:  2,
			Len:  GameStatusPayloadSize,
			buff: NewBufferMessage(sizeHeader),
		},
		CyclesOfDeath:    3,
		CyclesDone:       4,
		NumberOfLivesOps: 5,
		NumberOfChecks:   6,
		LastLivedPlayer:  7,
		Arena:            [4096]byte{},
		Setting:          [4096]byte{},
		buff:             NewBufferMessage(0),
	}

	a := genBinaryGameStatus(m)
	b := new(bytes.Buffer)
	e := m.Write(b)
	if e != nil {
		t.Errorf("Fail Write GameStatus: %v\n", e)
	}
	if !reflect.DeepEqual(a, b.Bytes()) {
		t.Errorf("Wrong answer: Write GameStatus\ngot:%v\nexp:%v\n", b.Bytes(), a)
	}

	b.Reset()
	b.Write(a)
	mm := NewGameStatus(NewBufferMessage(0))
	e = mm.Header.Read(b)
	if e != nil {
		t.Errorf("Fail Read Header: %v\n", e)
	}
	e = mm.Read(b)
	if e != nil {
		t.Errorf("Fail Read GameStatus: %v\n", e)
	}

	m.Header.buff = nil
	m.buff = nil
	mm.Header.buff = nil
	mm.buff = nil
	if !reflect.DeepEqual(m, mm) {
		t.Errorf("Wrong answer: Read GameStatus\ngot:%v\nexp:%v\n", mm, m)
	}
}
