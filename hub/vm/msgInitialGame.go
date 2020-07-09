package main

import (
	"bytes"
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
		err  error
		buff = new(bytes.Buffer)
	)

	if err = binary.Write(buff, binary.BigEndian, sg.Type); err != nil {
		return err
	}
	if err = binary.Write(buff, binary.BigEndian, sg.Id); err != nil {
		return err
	}
	if err = binary.Write(buff, binary.BigEndian, sg.Len); err != nil {
		return err
	}
	if err = binary.Write(buff, binary.BigEndian, sg.Number); err != nil {
		return err
	}
	if _, err = buff.Write(sg.Champs); err != nil {
		return err
	}
	if _, err = conn.Write(buff.Bytes()); err != nil {
		return err
	}

	return err
}

// TODO: delete smell code
func tmpInitialGame(conn net.Conn, n uint8) {
	var (
		msg InitialGame
		err error
	)

	msg.Type = TypeMsgInitialGame
	//msg.Type = 2
	sz := 2768
	msg.Id = rand.Uint32()
	msg.Number = n
	fmt.Println("GO INIT GAME")
	size := sz * int(n)
	msg.Len = uint32(size + 1)
	msg.Champs = make([]byte, size)
	for i := 0; i < int(n); i++ {
		file, err := os.Open("champs/slider2.cor")
		if err != nil {
			log.Fatal(err)
		}
		file.Read(msg.Champs[i*sz:])
		file.Close()
	}
	err = msg.Send(conn)
	if err != nil {
		fmt.Printf("ERROR send BOTS %v\n", err)
	}
	fmt.Printf("SEND GAME "+
		"{type:%d, id:%d, len:%d, number:%d}\n",
		msg.Type, msg.Id, msg.Len, msg.Number)
	//fmt.Printf("%+v\n", msg)
}
