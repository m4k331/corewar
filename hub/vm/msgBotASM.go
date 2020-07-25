package main

import (
	"bytes"
	"encoding/binary"
	"fmt"
	"net"
	"os"
)

type BotASM struct {
	Type uint8
	Id   uint32
	Len  uint32
	Bot  []byte
}

func MockSendValidBot(conn net.Conn) {
	path := "/Users/ahugh/go/src/corewar/hub/vm/champs/bee_gees.s"
	file, err := os.Open(path)
	if err != nil {
		panic(err)
	}
	info, err := file.Stat()
	if err != nil {
		panic(err)
	}
	bot := make([]byte, info.Size())
	n, err := file.Read(bot[:])
	if err != nil {
		panic(err)
	}
	if n != int(info.Size()) {
		panic(fmt.Sprintf("ERROR SIZE (%d/%d)", n, info.Size()))
	}
	msg := &BotASM{
		Type: TypeMsgSendBot,
		Id:   123,
		Len:  uint32(info.Size()),
		Bot:  bot,
	}
	err = msg.Send(conn)
	if err != nil {
		panic(err)
	}
	fmt.Printf("Send botASM {len: %d, bot: %s}\n", msg.Len, string(msg.Bot))
}

func MockSendInvalidBot(conn net.Conn) {
	path := "/Users/ahugh/go/src/corewar/hub/vm/champs/invalid_bee_gees.s"
	file, err := os.Open(path)
	if err != nil {
		panic(err)
	}
	info, err := file.Stat()
	if err != nil {
		panic(err)
	}
	bot := make([]byte, info.Size())
	n, err := file.Read(bot[:])
	if err != nil {
		panic(err)
	}
	if n != int(info.Size()) {
		panic(fmt.Sprintf("ERROR SIZE (%d/%d)", n, info.Size()))
	}
	msg := &BotASM{
		Type: TypeMsgSendBot,
		Id:   123,
		Len:  uint32(info.Size()),
		Bot:  bot,
	}
	err = msg.Send(conn)
	if err != nil {
		panic(err)
	}
	fmt.Printf("Send INVALID botASM {len: %d, bot: %s}\n", msg.Len, string(msg.Bot))
}

func MockSendInvalidSizeBot(conn net.Conn) {
	path := "/Users/ahugh/go/src/corewar/hub/vm/champs/bee_gees.s"
	file, err := os.Open(path)
	if err != nil {
		panic(err)
	}
	info, err := file.Stat()
	if err != nil {
		panic(err)
	}
	bot := make([]byte, info.Size())
	n, err := file.Read(bot[:])
	if err != nil {
		panic(err)
	}
	if n != int(info.Size()) {
		panic(fmt.Sprintf("ERROR SIZE (%d/%d)", n, info.Size()))
	}
	bot = bot[:len(bot)-2]
	msg := &BotASM{
		Type: TypeMsgSendBot,
		Id:   123,
		Len:  uint32(info.Size()),
		Bot:  bot,
	}
	err = msg.Send(conn)
	if err != nil {
		panic(err)
	}
	fmt.Printf("Send invalid size botASM {len: %d, botSize: %s}\n", msg.Len, string(msg.Bot))
}

func MockSendBadMsgASM(conn net.Conn) {
	var (
		err  error
		buff = new(bytes.Buffer)
	)

	msg := struct {
		Type uint8
		Id   uint32
		Len  uint32
	}{
		Type: 234,
		Id:   235,
		Len:  236,
	}

	if err = binary.Write(buff, binary.BigEndian, msg.Type); err != nil {
		panic(err)
	}
	if err = binary.Write(buff, binary.BigEndian, msg.Id); err != nil {
		panic(err)
	}
	if err = binary.Write(buff, binary.BigEndian, msg.Len); err != nil {
		panic(err)
	}
	if _, err = conn.Write(buff.Bytes()); err != nil {
		panic(err)
	}

	fmt.Printf("Send Bad message to ASM {type: %d, id: %d, len: %d}\n", msg.Type, msg.Id, msg.Len)
}

func (basm *BotASM) Send(conn net.Conn) error {
	var (
		err  error
		buff = new(bytes.Buffer)
	)

	if err = binary.Write(buff, binary.BigEndian, basm.Type); err != nil {
		return err
	}
	if err = binary.Write(buff, binary.BigEndian, basm.Id); err != nil {
		return err
	}
	if err = binary.Write(buff, binary.BigEndian, basm.Len); err != nil {
		return err
	}
	n, err := buff.Write(basm.Bot)
	if err != nil {
		return err
	}
	if n != len(basm.Bot) {
		return fmt.Errorf("Error writing to buffer: bad size (%d/%d) ", n, len(basm.Bot))
	}
	if _, err = conn.Write(buff.Bytes()); err != nil {
		return err
	}

	return err
}

func readBinaryASM(conn net.Conn) (*BotASM, error) {
	var (
		n int
		e error
		m = new(BotASM)
	)

	m.Type = TypeMsgBinaryASM
	if e = binary.Read(conn, binary.BigEndian, &m.Id); e != nil {
		return m, e
	}
	if e = binary.Read(conn, binary.BigEndian, &m.Len); e != nil {
		return m, e
	}
	m.Bot = make([]byte, m.Len)
	if n, e = conn.Read(m.Bot); n != int(m.Len) || e != nil {
		return m, fmt.Errorf("Error reading Message field (%d/%d): %v ", n, m.Len, e)
	}
	file, err := os.Create("bot.cor")
	if err != nil {
		panic(err)
	}
	n, err = file.Write(m.Bot[:])
	if err != nil {
		panic(err)
	}
	if n != len(m.Bot) {
		panic(fmt.Errorf("%d/%d", n, len(m.Bot)))
	}
	return m, e
}

func handleBinaryASM(conn net.Conn) error {
	var (
		err  error
		msg  *BotASM
		addr = conn.RemoteAddr().String()
	)

	msg, err = readBinaryASM(conn)
	if err != nil {
		return fmt.Errorf("Error reading msg: %v ", err)
	}
	fmt.Printf("Hub received Binary ASM msg from %s\n", addr)

	// TODO: send Binary ASM on web site
	fmt.Printf("Hub send Binary ASM on web site "+
		"{id: %d, len: %d, bot: [%v]}\n",
		msg.Id, msg.Len, string(msg.Bot))

	return err
}
