package main

import (
	"io"
)

type BufferMessage struct {
	buff []byte
}

func NewBufferMessage(size int) *BufferMessage {
	return &BufferMessage{buff: make([]byte, size)}
}

func (b *BufferMessage) Resize(n int) {
	switch {
	case n < 0:
	case n > cap(b.buff):
		b.buff = make([]byte, n)
	default:
		b.buff = b.buff[:n]
	}
}

func (b *BufferMessage) ReadN(r io.Reader, n int) error {
	var (
		e          error
		offset, rb int
	)

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

func (b *BufferMessage) Read(p []byte) (n int, e error) {
	switch {
	case len(p) > len(b.buff):
		copy(p, b.buff[:])
		e = io.EOF
		n = len(b.buff)
	default:
		copy(p, b.buff[:len(p)])
		n = len(p)
	}
	return n, e
}
