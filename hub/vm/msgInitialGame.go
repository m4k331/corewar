package main

import (
	"encoding/binary"
	"math/rand"
	"net"
)

type InitialGame struct {
	Type   uint8
	Id     uint32
	Len    uint32
	Number uint8
	Champs []byte
}

func (sg InitialGame) Send(conn net.Conn) error {
	var err error

	if err = binary.Write(conn, binary.BigEndian, &sg.Type); err != nil {
		return err
	}
	if err = binary.Write(conn, binary.BigEndian, &sg.Id); err != nil {
		return err
	}
	if err = binary.Write(conn, binary.BigEndian, &sg.Len); err != nil {
		return err
	}
	if err = binary.Write(conn, binary.BigEndian, &sg.Number); err != nil {
		return err
	}
	if err = binary.Write(conn, binary.BigEndian, sg.Champs); err != nil {
		return err
	}

	return err
}

func tmpInitialGame(conn net.Conn, n uint8) {
	var (
		msg InitialGame
	)

	msg.Type = TypeMsgInitialGame
	msg.Id = rand.Uint32()
	msg.Number = n

}
