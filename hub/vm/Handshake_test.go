package main

import (
	"bytes"
	"encoding/binary"
	"reflect"
	"testing"
)

func TestHandshake(t *testing.T) {
	a := []byte{1, 0, 0, 0, 2, 0, 0, 0, 0} // DON'T EDIT!!!!!!!1111
	ba := bytes.NewBuffer(a)
	h := NewHeader(NewBufferMessage(sizeHeader))

	e := h.Read(ba)
	if e != nil {
		t.Errorf("Fail read Header: %v\n", e)
	}

	m := NewHandshake(NewBufferMessage(0))
	m.SetHeader(h)
	e = m.Read(ba)
	if e != nil {
		t.Errorf("Fail Read Handshake (body empty):%v\n", e)
	}
	if h.Type != m.Header.Type || h.Key != m.Header.Key || h.Len != m.Header.Len {
		t.Errorf("Wrong answer: Read Handshake (body empty)\ngot:%v\nexp:%v\n", m.Header, h)
	}

	e = m.Write(ba)
	if e != nil {
		t.Errorf("Fail Write Handshake (body empty):%v\n", e)
	}
	if !reflect.DeepEqual(a, ba.Bytes()) {
		t.Errorf("Wrong anwer: Write Handshake (body empty)\ngot:%v\nexp:%v\n", ba.Bytes(), a)
	}

	ports := []uint32{9, 8, 7, 6}
	ba.Reset()
	for _, p := range ports {
		if e = binary.Write(ba, binary.BigEndian, &p); e != nil {
			t.Errorf("[port:%d] binary write error: %v\n", p, e)
		}
	}

	m.Len = 4 * 4
	e = m.Read(ba)
	if e != nil {
		t.Errorf("Fail Read Handshake (full):%v\n", e)
	}
	if !reflect.DeepEqual(ports, m.Ports) {
		t.Errorf("Wrong answer: Read Handshake (full)\ngot:%v\nexp:%v\n", m.Ports, ports)
	}

	a = []byte{1, 0, 0, 0, 2, 0, 0, 0, 16, 0, 0, 0, 9, 0, 0, 0, 8, 0, 0, 0, 7, 0, 0, 0, 6} // DON'T EDIT!!!!!!!1111
	ba.Reset()
	e = m.Write(ba)
	if e != nil {
		t.Errorf("Fail Write Handshake (full):%v\n", e)
	}
	if !reflect.DeepEqual(a, ba.Bytes()) {
		t.Errorf("Wrong answer: Write Handshake (full)\ngot:%v\nexp:%v\n", ba.Bytes(), a)
	}
}
