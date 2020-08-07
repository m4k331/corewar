package main

import (
	"encoding/binary"
	"io"
)

const sizeHeader = 9

type Header struct {
	Type uint8
	Key  uint32
	Len  uint32
	buff *BufferMessage
}

func (h *Header) Read(r io.Reader) (e error) {
	h.buff.Reset()
	if e = h.buff.ReadN(r, sizeHeader); e != nil {
		return e
	}
	if e = binary.Read(h.buff, binary.BigEndian, &h.Type); e != nil {
		return e
	}
	if e = binary.Read(h.buff, binary.BigEndian, &h.Key); e != nil {
		return e
	}
	return binary.Read(h.buff, binary.BigEndian, &h.Len)
}

func (h *Header) Write(w io.Writer) (e error) {
	h.buff.Reset()
	if e = binary.Write(h.buff, binary.BigEndian, &h.Type); e != nil {
		return e
	}
	if e = binary.Write(h.buff, binary.BigEndian, &h.Key); e != nil {
		return e
	}
	if e = binary.Write(h.buff, binary.BigEndian, &h.Len); e != nil {
		return e
	}
	return h.buff.WriteN(w, sizeHeader)
}
