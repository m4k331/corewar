package main

import (
	"bytes"
	"encoding/binary"
	"reflect"
	"testing"
)

func genBinaryEndOfGame(m *EndOfGame) []byte {
	b := new(bytes.Buffer)
	_ = binary.Write(b, binary.BigEndian, &m.Type)
	_ = binary.Write(b, binary.BigEndian, &m.Key)
	_ = binary.Write(b, binary.BigEndian, &m.Len)
	_ = binary.Write(b, binary.BigEndian, &m.Winner)
	b.Write(m.Message)
	return b.Bytes()
}

func TestEndOfGame(t *testing.T) {
	m := &EndOfGame{
		Header: Header{
			Type: 1,
			Key:  2,
			Len:  11,
			buff: NewBufferMessage(sizeHeader),
		},
		Winner:  3,
		Message: []byte("1234567890"),
		buff:    NewBufferMessage(0),
	}

	a := genBinaryEndOfGame(m)
	b := new(bytes.Buffer)
	e := m.Write(b)
	if e != nil {
		t.Errorf("Fail Write EndOfGame: %v\n", e)
	}
	if !reflect.DeepEqual(a, b.Bytes()) {
		t.Errorf("Wrong answer: Write EndOfGame\ngot:%v\nexp:%v\n", b.Bytes(), a)
	}

	b.Reset()
	b.Write(a)
	mm := NewEndOfGame(NewBufferMessage(0))
	e = mm.Header.Read(b)
	if e != nil {
		t.Errorf("Fail Read Header: %v\n", e)
	}
	e = mm.Read(b)
	if e != nil {
		t.Errorf("Fail Read EndOfGame: %v\n", e)
	}

	m.Header.buff = nil
	m.buff = nil
	mm.Header.buff = nil
	mm.buff = nil
	if !reflect.DeepEqual(m, mm) {
		t.Errorf("Wrong answer: Read EndOfGame\ngot:%v\nexp:%v\n", mm, m)
	}
}
