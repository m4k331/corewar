package main

import (
	"bytes"
	"encoding/binary"
	"reflect"
	"testing"
)

func genBinaryInitialGame(m *InitialGame) []byte {
	b := new(bytes.Buffer)
	_ = binary.Write(b, binary.BigEndian, &m.Type)
	_ = binary.Write(b, binary.BigEndian, &m.Key)
	_ = binary.Write(b, binary.BigEndian, &m.Len)
	_ = binary.Write(b, binary.BigEndian, &m.Number)
	b.Write(m.Champs)
	return b.Bytes()
}

func TestInitialGame(t *testing.T) {
	m := &InitialGame{
		Header: Header{
			Type: 1,
			Key:  2,
			Len:  11,
			buff: NewBufferMessage(sizeHeader),
		},
		Number: 3,
		Champs: []byte("1234567890"),
		buff:   NewBufferMessage(0),
	}

	a := genBinaryInitialGame(m)
	b := new(bytes.Buffer)
	e := m.Write(b)
	if e != nil {
		t.Errorf("Fail Write InitialGame: %v\n", e)
	}
	if !reflect.DeepEqual(a, b.Bytes()) {
		t.Errorf("Wrong answer: Write InitialGame\ngot:%v\nexp:%v\n", b.Bytes(), a)
	}

	b.Reset()
	b.Write(a)
	mm := NewInitialGame(NewBufferMessage(0))
	e = mm.Header.Read(b)
	if e != nil {
		t.Errorf("Fail Read Header: %v\n", e)
	}
	e = mm.Read(b)
	if e != nil {
		t.Errorf("Fail Read InitialGame: %v\n", e)
	}

	m.Header.buff = nil
	m.buff = nil
	mm.Header.buff = nil
	mm.buff = nil
	if !reflect.DeepEqual(m, mm) {
		t.Errorf("Wrong answer: Read InitialGame\ngot:%v\nexp:%v\n", mm, m)
	}
}
