package main

import (
	"bytes"
	"io"
	"reflect"
	"testing"
)

func TestBufferMessage(t *testing.T) {
	a := make([]byte, 50)
	r := bytes.NewBuffer(a)
	b := NewBufferMessage(50)
	for i := range a {
		a[i] = byte(i)
		b.buff[i] = byte(i)
	}

	// TEST #1
	n := 10
	e := b.ReadN(r, n)
	if e != nil {
		t.Errorf("1. Fail test ReadN bytes: %v\n", e)
	}
	a = []byte{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
	if !reflect.DeepEqual(b.buff, a) {
		t.Errorf("1. Fail test ReadN: [Read size %d]\ngot:%v\nexp:%v\n", n, b.buff, a)
	}

	// TEST #2
	l := n
	g := make([]byte, l)
	n, e = b.Write(g)
	if e != nil {
		t.Errorf("2. Fail test Write: [%v]\n", e)
	}
	if n != l {
		t.Errorf("2. Fail test Write:\ngot size:%d\nexp size:%d\n", n, l)
	}
	if !reflect.DeepEqual(g, a) {
		t.Errorf("2. Fail test Write:\ngot:%v\nexp:%v\n", g, a)
	}

	// TEST #3
	n = 0
	a = []byte{}
	e = b.ReadN(r, n)
	if e != nil {
		t.Errorf("3. Fail test ReadN: [%v]\n", e)
	}
	if !reflect.DeepEqual(b.buff, []byte{}) {
		t.Errorf("3. Fail test ReadN: [Read size %d]\ngot:%v\nexp:%v\n", n, b.buff, a)
	}

	// TEST #4
	l = n
	g = make([]byte, l)
	n, e = b.Write(g)
	if e != nil {
		t.Errorf("4. Fail test Write: [%v]\n", e)
	}
	if n != l {
		t.Errorf("4. Fail test Write:\ngot size:%d\nexp size:%d\n", n, l)
	}
	if !reflect.DeepEqual(g, a) {
		t.Errorf("4. Fail test Write:\ngot:%v\nexp:%v\n", g, a)
	}

	// TEST #5
	n = 410
	a = []byte{10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49}
	e = b.ReadN(r, 410)
	if !reflect.DeepEqual(b.buff, a) {
		t.Errorf("5. Fail test ReadN: [Read size %d]\ngot:%v\nexp:%v\n", n, b.buff, a)
	}

	// TEST #6
	l = n
	g = make([]byte, l)
	n, e = b.Write(g)
	if e != io.EOF {
		t.Errorf("6. Fail test Write: [%v]\n", e)
	}
	if n != len(a) {
		t.Errorf("6. Fail test Write:\ngot size:%d\nexp size:%d\n", n, len(a))
	}
	a = append(a, make([]byte, l-len(a))...)
	if !reflect.DeepEqual(g, a) {
		t.Errorf("6. Fail test Write:\ngot:%v\nexp:%v\n", g, a)
	}

	// TEST #7
	a = []byte{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
	n, e = b.Read(a)
	if e != nil {
		t.Errorf("7. Fail test Read: [%v]\n", e)
	}
	if n != len(a) {
		t.Errorf("7. Fail test Read:\ngot size:%d\nexp size:%d\n", n, len(a))
	}
	if !reflect.DeepEqual(b.buff, a) {
		t.Errorf("7. Fail test Read:\ngot:%v\nexp:%v\n", b.buff, a)
	}

	// TEST #8
	n, e = b.Read(a)
	if e != nil {
		t.Errorf("8. Fail test Read: [%v]\n", e)
	}
	if n != len(a) {
		t.Errorf("8. Fail test Read:\ngot size:%d\nexp size:%d\n", n, len(a))
	}
	a = append(a, a...)
	if !reflect.DeepEqual(b.buff, a) {
		t.Errorf("8. Fail test Read:\ngot:%v\nexp:%v\n", b.buff, a)
	}

	// TEST #9
	var i int

	for i < 5 {
		n, e = b.Read(a)
		if e != nil {
			t.Errorf("9.%d Fail test Read: [%v]\n", i, e)
		}
		if n != len(a) {
			t.Errorf("9.%d Fail test Read:\ngot size:%d\nexp size:%d\n", i, n, len(a))
		}
		a = append(a, a...)
		i++
	}
	if !reflect.DeepEqual(b.buff, a) {
		t.Errorf("9.%d Fail test Read:\ngot:%v\nexp:%v\n", i, b.buff, a)
	}

}
