package main

import (
	"encoding/binary"
	"fmt"
	"log"
	"math/rand"
	"net"
	"os"
)

type InitialGame struct {
	Type   uint8
	Id     uint32
	Len    uint32
	Number uint8
	Champs []byte
}

func (sg InitialGame) Send(conn net.Conn) error {
	var (
		err error
	)

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
	if _, err = conn.Write(sg.Champs); err != nil {
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
	fmt.Println("GO INIT GAME")
	file, err := os.Open("champs/ex.cor")
	if err != nil {
		log.Fatal(err)
	}
	size := 2215 * int(n)
	msg.Len = uint32(size + 1)
	msg.Champs = make([]byte, size)
	for i := 0; i < int(n); i++ {
		file.Read(msg.Champs[i*2215:])
	}
	err = msg.Send(conn)
	if err != nil {
		fmt.Printf("ERROR send BOTS %v\n", err)
	}
	fmt.Printf("SEND GAME " +
		"{type:%d, id:%d, len:%d, number:%d}\n",
		msg.Type, msg.Id, msg.Len, msg.Number)
	fmt.Printf("%+v\n", msg)
}
