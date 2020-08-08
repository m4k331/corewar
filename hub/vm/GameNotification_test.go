package main

import (
	"bytes"
	"encoding/binary"
	"reflect"
	"testing"
)

func TestGameNotification(t *testing.T) {
	a := []byte{1, 0, 0, 0, 2, 0, 0, 0, 4, 0, 0, 0, 0} // DON'T EDIT!!!!!!!1111
	ba := bytes.NewBuffer(a)
	h := NewHeader(NewBufferMessage(sizeHeader))

	e := h.Read(ba)
	if e != nil {
		t.Errorf("Fail read Header: %v\n", e)
	}

	m := NewGameNotification(NewBufferMessage(0))
	m.SetHeader(h)
	e = m.Read(ba)
	if e != nil {
		t.Errorf("Fail Read GameNotification (body empty):%v\n", e)
	}
	if h.Type != m.Header.Type || h.Key != m.Header.Key || h.Len != m.Header.Len {
		t.Errorf("Wrong answer: Read GameNotification (body empty)\ngot:%v\nexp:%v\n", m.Header, h)
	}

	e = m.Write(ba)
	if e != nil {
		t.Errorf("Fail Write GameNotification (body empty):%v\n", e)
	}
	if !reflect.DeepEqual(a, ba.Bytes()) {
		t.Errorf("Wrong anwer: Write GameNotification (body empty)\ngot:%v\nexp:%v\n", ba.Bytes(), a)
	}

	var socket uint32 = 7
	ba.Reset()
	e = binary.Write(ba, binary.BigEndian, &socket)
	if e != nil {
		t.Errorf("Error binary write: %v\n", e)
	}
	m.Len = 4
	e = m.Read(ba)
	if e != nil {
		t.Errorf("Fail Read GameNotification (full):%v\n", e)
	}
	if m.Socket != socket {
		t.Errorf("Wrong answer: Read GameNotification (full)\ngot:%v\nexp:%v\n", m.Socket, socket)
	}

	a = []byte{1, 0, 0, 0, 2, 0, 0, 0, 4, 0, 0, 0, 7} // DON'T EDIT!!!!!!!1111
	ba.Reset()
	e = m.Write(ba)
	if e != nil {
		t.Errorf("Fail Write GameNotification (full):%v\n", e)
	}
	if !reflect.DeepEqual(a, ba.Bytes()) {
		t.Errorf("Wrong answer: Write GameNotification (full)\ngot:%v\nexp:%v\n", ba.Bytes(), a)
	}
}
