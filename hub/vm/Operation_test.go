package main

import (
	"bytes"
	"encoding/binary"
	"reflect"
	"testing"
)

func genBinaryOperation(m *Operation) []byte {
	b := new(bytes.Buffer)
	_ = binary.Write(b, binary.BigEndian, &m.Type)
	_ = binary.Write(b, binary.BigEndian, &m.Key)
	_ = binary.Write(b, binary.BigEndian, &m.Len)
	_ = binary.Write(b, binary.BigEndian, &m.ProcId)
	_ = binary.Write(b, binary.BigEndian, &m.ProcPos)
	b.Write(m.Message)
	return b.Bytes()
}

func TestOperation(t *testing.T) {
	m := &Operation{
		Header: Header{
			Type: 1,
			Key:  2,
			Len:  16,
			buff: NewBufferMessage(sizeHeader),
		},
		ProcId:  3,
		ProcPos: 4,
		Message: []byte("1234567890"),
		buff:    NewBufferMessage(0),
	}

	a := genBinaryOperation(m)
	b := new(bytes.Buffer)
	e := m.Write(b)
	if e != nil {
		t.Errorf("Fail Write Operation: %v\n", e)
	}
	if !reflect.DeepEqual(a, b.Bytes()) {
		t.Errorf("Wrong answer: Write Operation\ngot:%v\nexp:%v\n", b.Bytes(), a)
	}

	b.Reset()
	b.Write(a)
	mm := NewOperation(NewBufferMessage(0))
	e = mm.Header.Read(b)
	if e != nil {
		t.Errorf("Fail Read Header: %v\n", e)
	}
	e = mm.Read(b)
	if e != nil {
		t.Errorf("Fail Read Operation: %v\n", e)
	}

	m.Header.buff = nil
	m.buff = nil
	mm.Header.buff = nil
	mm.buff = nil
	if !reflect.DeepEqual(m, mm) {
		t.Errorf("Wrong answer: Read Operation\ngot:%v\nexp:%v\n", mm, m)
	}
}
