package main

import (
	"io"
)

type BufferMessage struct {
	buff []byte
}

func NewBufferMessage(capacity int) *BufferMessage {
	return &BufferMessage{buff: make([]byte, 0, capacity)}
}

func (b *BufferMessage) Bytes() []byte {
	return b.buff
}

func (b *BufferMessage) Reset() {
	b.Resize(0)
}

func (b *BufferMessage) Resize(n int) {
	switch {
	case n < 0:
	case n > cap(b.buff):
		fat := make([]byte, n)
		copy(fat, b.buff[:cap(b.buff)])
		b.buff = fat
	default:
		b.buff = b.buff[:n]
	}
}

func (b *BufferMessage) Read(p []byte) (n int, e error) {
	switch {
	case len(p) > len(b.buff):
		n = len(b.buff)
		e = io.EOF
	default:
		n = len(p)
	}
	copy(p, b.buff[:n])
	b.buff = b.buff[n:]
	return n, e
}

func (b *BufferMessage) ReadN(r io.Reader, n int) (e error) {
	var (
		rb     int
		offset = len(b.buff)
	)

	n += offset
	b.Resize(n)
	for offset < n {
		rb, e = r.Read(b.buff[offset:])
		if e != nil {
			b.Resize(offset + rb)
			break
		}
		offset += rb
	}
	return e
}

func (b *BufferMessage) Write(p []byte) (n int, e error) {
	n = len(p)
	offset := len(b.buff)
	b.Resize(offset + n)
	copy(b.buff[offset:], p)
	return n, e
}

func (b *BufferMessage) WriteN(w io.Writer, n int) (e error) {
	if n > len(b.buff) {
		n = len(b.buff)
	}

	var offset, wb int

	for offset < n {
		wb, e = w.Write(b.buff[:n-offset])
		if e != nil {
			break
		}
		offset += wb
	}
	return e
}
