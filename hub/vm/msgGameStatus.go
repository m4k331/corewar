package main

import (
	"encoding/binary"
	"fmt"
	"net"
)

const ArenaSize = 4096

type GameStatus struct {
	Type             uint8
	Id               uint32
	Len              uint32
	CyclesOfDeath    uint32
	CyclesDone       uint32
	NumberOfLivesOps uint32
	NumberOfChecks   uint32
	LastLivedPlayer  uint8
	Arena            [ArenaSize]byte
	Setting          [ArenaSize]byte
}

func readGameStatus(conn net.Conn) (*GameStatus, error) {
	var (
		n int
		e error
		m = new(GameStatus)
	)
	m.Type = TypeMsgGameStatus
	if e = binary.Read(conn, binary.BigEndian, &m.Id); e != nil {
		return m, e
	}
	if e = binary.Read(conn, binary.BigEndian, &m.Len); e != nil {
		return m, e
	}
	if e = binary.Read(conn, binary.BigEndian, &m.CyclesOfDeath); e != nil {
		return m, e
	}
	if e = binary.Read(conn, binary.BigEndian, &m.CyclesDone); e != nil {
		return m, e
	}
	if e = binary.Read(conn, binary.BigEndian, &m.NumberOfLivesOps); e != nil {
		return m, e
	}
	if e = binary.Read(conn, binary.BigEndian, &m.NumberOfChecks); e != nil {
		return m, e
	}
	if e = binary.Read(conn, binary.BigEndian, &m.LastLivedPlayer); e != nil {
		return m, e
	}
	if n, e = conn.Read(m.Arena[:]); n != ArenaSize || e != nil {
		return m, fmt.Errorf("Error reading areana field (%d/%d): %v ", n, ArenaSize, e)
	}
	if n, e = conn.Read(m.Setting[:]); n != ArenaSize || e != nil {
		return m, fmt.Errorf("Error reading setting field (%d/%d): %v ", n, ArenaSize, e)
	}
	return m, e
}

func handleGameStatus(conn net.Conn) error {
	var (
		err  error
		msg  *GameStatus
		addr = conn.RemoteAddr().String()
	)

	msg, err = readGameStatus(conn)
	if err != nil {
		return fmt.Errorf("Error reading msg: %v ", err)
	}
	fmt.Printf("Hub received a game status msg from %s\n", addr)

	// TODO: send game on web site
	fmt.Printf("Hub send game on web site "+
		"{id: %d; len: %d, death: %d, cycles: %d, "+
		"livesOps: %d, checks: %d, llp: %d}\n",
		msg.Id,
		msg.Len,
		msg.CyclesOfDeath,
		msg.CyclesDone,
		msg.NumberOfLivesOps,
		msg.NumberOfChecks,
		msg.LastLivedPlayer,
	)
	return err
}
