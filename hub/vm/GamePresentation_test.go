package main

import (
	"bytes"
	"reflect"
	"testing"
)

func TestGamePresentation(t *testing.T) {
	a := []byte{1, 0, 0, 0, 2, 0, 0, 0, 0} // DON'T EDIT!!!!!!!1111
	ba := bytes.NewBuffer(a)
	h := NewHeader(NewBufferMessage(sizeHeader))

	e := h.Read(ba)
	if e != nil {
		t.Errorf("Fail read Header: %v\n", e)
	}

	m := NewGamePresentation(NewBufferMessage(0))
	m.SetHeader(h)
	e = m.Read(ba)
	if e != nil {
		t.Errorf("Fail Read GamePresentation (body empty):%v\n", e)
	}
	if h.Type != m.Header.Type || h.Key != m.Header.Key || h.Len != m.Header.Len {
		t.Errorf("Wrong answer: Read GamePresentation (body empty)\ngot:%v\nexp:%v\n", m.Header, h)
	}

	e = m.Write(ba)
	if e != nil {
		t.Errorf("Fail Write GamePresentation (body empty):%v\n", e)
	}
	if !reflect.DeepEqual(a, ba.Bytes()) {
		t.Errorf("Wrong anwer: Write GamePresentation (body empty)\ngot:%v\nexp:%v\n", ba.Bytes(), a)
	}

	ba.Reset()
	a = []byte("Hello!")
	ba.Write(a)
	m.Len = 6
	e = m.Read(ba)
	if e != nil {
		t.Errorf("Fail Read GamePresentation (full):%v\n", e)
	}
	if !reflect.DeepEqual(m.Comment, a) {
		t.Errorf("Wrong answer: Read GamePresentation (full)\ngot:%v\nexp:%v\n", m.Comment, a)
	}

	a = []byte{1, 0, 0, 0, 2, 0, 0, 0, 6} // DON'T EDIT!!!!!!!1111
	a = append(a, []byte("Hello!")...)
	ba.Reset()
	e = m.Write(ba)
	if e != nil {
		t.Errorf("Fail Write GamePresentation (full):%v\n", e)
	}
	if !reflect.DeepEqual(a, ba.Bytes()) {
		t.Errorf("Wrong answer: Write GamePresentation (full)\ngot:%v\nexp:%v\n", ba.Bytes(), a)
	}
}
