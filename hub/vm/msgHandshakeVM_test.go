package main

import (
	"bytes"
	"encoding/binary"
	"reflect"
	"testing"
)

func TestHandshakeVM(t *testing.T) {
	a := []byte{1, 0, 0, 0, 2, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} // DON'T EDIT!!!!!!!1111
	ba := bytes.NewBuffer(a)
	h := NewHeader(NewBufferMessage(sizeHeader))

	e := h.Read(ba)
	if e != nil {
		t.Errorf("Fail read Header: %v\n", e)
	}

	m := NewHandshakeVM(NewBufferMessage(0))
	m.SetHeader(h)
	e = m.Read(ba)
	if e != nil {
		t.Errorf("Fail Read HandshakeVM (body empty):%v\n", e)
	}
	if h.Type != m.Header.Type || h.Key != m.Header.Key || h.Len != m.Header.Len {
		t.Errorf("Wrong answer: Read HandshakeVM (body empty)\ngot:%v\nexp:%v\n", m.Header, h)
	}

	e = m.Write(ba)
	if e != nil {
		t.Errorf("Fail Write HandshakeVM (body empty):%v\n", e)
	}
	if !reflect.DeepEqual(a, ba.Bytes()) {
		t.Errorf("Wrong anwer: Write HandshakeVM (body empty)\ngot:%v\nexp:%v\n", ba.Bytes(), a)
	}

	ports := []uint32{9, 8, 7, 6}
	ba.Reset()
	for _, p := range ports {
		if e = binary.Write(ba, binary.BigEndian, &p); e != nil {
			t.Errorf("[port:%d] binary write error: %v\n", p, e)
		}
	}

	e = m.Read(ba)
	if e != nil {
		t.Errorf("Fail Read HandshakeVM (full):%v\n", e)
	}
	if !reflect.DeepEqual(ports, m.Ports) {
		t.Errorf("Wrong answer: Read HandshakeVM (full)\ngot:%v\nexp:%v\n", m.Ports, ports)
	}

	a = []byte{1, 0, 0, 0, 2, 0, 0, 0, 4, 0, 0, 0, 9, 0, 0, 0, 8, 0, 0, 0, 7, 0, 0, 0, 6} // DON'T EDIT!!!!!!!1111
	ba.Reset()
	e = m.Write(ba)
	if e != nil {
		t.Errorf("Fail Write HandshakeVM (full):%v\n", e)
	}
	if !reflect.DeepEqual(a, ba.Bytes()) {
		t.Errorf("Wrong answer: Write HandshakeVM (full)\ngot:%v\nexp:%v\n", ba.Bytes(), a)
	}
}
