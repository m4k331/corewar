package main

import (
	"bytes"
	"fmt"
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
	}

	// TEST #1
	n := 10
	d := r.Bytes()
	e := b.ReadN(r, n)
	if e != nil {
		t.Errorf("1.1 Fail test ReadN bytes: %v\n", e)
	}
	a = []byte{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
	if !reflect.DeepEqual(b.buff, a) {
		t.Errorf("1.2 Fail test ReadN (Testing b.buff)\nsize %d\ngot:%v\nexp:%v\n", n, b.buff, a)
	}
	if !reflect.DeepEqual(d[n:], r.Bytes()) {
		t.Errorf("1.3 Fail test ReadN: (Testing reader)\nsize %d\ngot:%v\nexp:%v\n", n, b.buff, a)
	}

	// TEST #2
	l := n
	g := make([]byte, l)
	n, e = b.Write(g)
	if e != nil {
		t.Errorf("2.1 Fail test Write bytes: [%v]\n", e)
	}
	if n != l {
		t.Errorf("2.2 Fail test Write (number of bytes written)\ngot size:%d\nexp size:%d\n", n, l)
	}
	if !reflect.DeepEqual(g, a) {
		t.Errorf("2.3 Fail test Write (Testing written g buffer)\ngot:%v\nexp:%v\n", g, a)
	}
	a = []byte{}
	if !reflect.DeepEqual(b.buff, a) {
		t.Errorf("2.4 Fail test Write (not empty b.buff)\ngot:%v\nexp:%v\n", b.buff, a)
	}

	// TEST #3
	n = 0
	a = []byte{}
	e = b.ReadN(r, n)
	if e != nil {
		t.Errorf("3.1 Fail test ReadN bytes: [%v]\n", e)
	}
	if !reflect.DeepEqual(b.buff, []byte{}) {
		t.Errorf("3.2 Fail test ReadN (not empty b.buff)\nRead size %d\ngot:%v\nexp:%v\n", n, b.buff, a)
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

	// TEST #10
	n = 5
	a = []byte{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
	w := bytes.NewBuffer(make([]byte, 0, 10))
	e = b.WriteN(w, n)
	if e != nil {
		t.Errorf("10. Fail test WriteN: [%v]\n", e)
	}
	if n != len(w.Bytes()) {
		t.Errorf("10. Fail test WriteN:\ngot size:%d\nexp size:%d\n", n, len(a))
	}
	if !reflect.DeepEqual(a[:n], w.Bytes()) {
		t.Errorf("10. Fail test WriteN:\ngot:%v\nexp:%v\n", b.buff, a)
	}

	// TEST 11
	fake := new(fakeWriter)
	e = b.WriteN(fake, 100)
	if e == nil {
		t.Errorf("11. Fail test WriteN: [%v]\n", e)
	}

	// TEST #12
	b.Reset()
	if len(b.buff) != 0 {
		t.Errorf("12. Fail test Reset:\ngot size:%d\nexp size:%d\n", 0, len(b.buff))
	}

	// TEST #13
	e = b.WriteN(w, 100)
	a = []byte{}
	if e != nil {
		t.Errorf("13. Fail test WriteN: [%v]\n", e)
	}
	if !reflect.DeepEqual(b.buff, a) {
		t.Errorf("13. Fail test WriteN:\ngot:%v\nexp:%v\n", b.buff, a)
	}
}

type fakeWriter struct {
}

func (f *fakeWriter) Write(p []byte) (n int, e error) {
	return 0, fmt.Errorf("fake error")
}
