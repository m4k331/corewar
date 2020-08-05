package main

import (
	"bytes"
	"io"
	"reflect"
	"testing"
)

func TestBufferMessageRead(t *testing.T) {
	a := make([]byte, 50)
	r := bytes.NewBuffer(a)
	b := NewBufferMessage(50)
	for i := range a {
		a[i] = byte(i)
		b.buff[i] = byte(i)
	}

	n := 10
	e := b.ReadN(r, n)
	if e != nil {
		t.Errorf("1. Fail test ReadN bytes: %v\n", e)
	}
	a = []byte{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
	if !reflect.DeepEqual(b.buff, a) {
		t.Errorf("1. Fail test ReadN: [Read size %d]\ngot:%v\nexp:%v\n", n, b.buff, a)
	}

	l := n
	g := make([]byte, l)
	n, e = b.Read(g)
	if e != nil {
		t.Errorf("2. Fail test Read: [%v]\n", e)
	}
	if n != l {
		t.Errorf("2. Fail test Read:\ngot size:%d\nexp size:%d\n", n, l)
	}
	if !reflect.DeepEqual(g, a) {
		t.Errorf("2. Fail test Read:\ngot:%v\nexp:%v\n", g, a)
	}

	n = 0
	a = []byte{}
	e = b.ReadN(r, n)
	if e != nil {
		t.Errorf("3. Fail test ReadN: [%v]\n", e)
	}
	if !reflect.DeepEqual(b.buff, []byte{}) {
		t.Errorf("3. Fail test ReadN: [Read size %d]\ngot:%v\nexp:%v\n", n, b.buff, a)
	}

	l = n
	g = make([]byte, l)
	n, e = b.Read(g)
	if e != nil {
		t.Errorf("4. Fail test Read: [%v]\n", e)
	}
	if n != l {
		t.Errorf("4. Fail test Read:\ngot size:%d\nexp size:%d\n", n, l)
	}
	if !reflect.DeepEqual(g, a) {
		t.Errorf("4. Fail test Read:\ngot:%v\nexp:%v\n", g, a)
	}

	n = 410
	a = []byte{10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49}
	e = b.ReadN(r, 410)
	if !reflect.DeepEqual(b.buff, a) {
		t.Errorf("5. Fail test ReadN: [Read size %d]\ngot:%v\nexp:%v\n", n, b.buff, a)
	}

	l = n
	g = make([]byte, l)
	n, e = b.Read(g)
	if e != io.EOF {
		t.Errorf("6. Fail test Read: [%v]\n", e)
	}
	if n != len(a) {
		t.Errorf("6. Fail test Read:\ngot size:%d\nexp size:%d\n", n, len(a))
	}
	a = append(a, make([]byte, l-len(a))...)
	if !reflect.DeepEqual(g, a) {
		t.Errorf("6. Fail test Read:\ngot:%v\nexp:%v\n", g, a)
	}
}
