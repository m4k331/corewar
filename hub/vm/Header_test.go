package main

import (
	"bytes"
	"reflect"
	"testing"
)

func TestHeader(t *testing.T) {
	h := Header{
		Type: 1,
		Key:  2,
		Len:  3,
		buff: NewBufferMessage(sizeHeader),
	}
	a := []byte{1, 0, 0, 0, 2, 0, 0, 0, 3}
	b := new(bytes.Buffer)
	if e := h.Write(b); e != nil {
		t.Errorf("Header: Writer error")
	}
	if !reflect.DeepEqual(b.Bytes(), a) {
		t.Errorf("Header: wrong buffer\ngot:%v\nexp:%v\n", b.Bytes(), a)
	}

	ah := Header{
		Type: 3,
		Key:  4,
		Len:  5,
		buff: NewBufferMessage(sizeHeader),
	}
	b.Reset()
	if e := ah.Write(b); e != nil {
		t.Errorf("Header: Writer error")
	}
	b = bytes.NewBuffer(ah.buff.Bytes())
	if e := h.Read(b); e != nil {
		t.Errorf("Header: Reader error\n")
	}
	h.buff = nil
	ah.buff = nil
	if !reflect.DeepEqual(h, ah) {
		t.Errorf("Header: wrong header\ngot:%v\nexp:%v\n", h, ah)
	}
}
