package job

import (
	"cw/hub/utils"
	"errors"
	"time"
)

// TODO: add to config
const DatabusTimeout = time.Second * 3

var (
	ErrDatabus = errors.New("databus unavailable")
)

type Databus struct {
	Type      string
	Available bool
	in        chan interface{}
	out       chan interface{}
	close     chan interface{}
}

func NewDatabus(_type string) *Databus {
	return &Databus{
		Type:      _type,
		Available: true,
		in:        make(chan interface{}, 1),
		out:       make(chan interface{}, 1),
		close:     make(chan interface{}, 1),
	}
}

func (ctr *Databus) In(data interface{}) error {
	if ctr.Available {
		select {
		case ctr.in <- data:
			return nil
		case <-ctr.close:
			ctr.Close()
		case <-time.NewTimer(DatabusTimeout).C:
			ctr.Close()
		}
	}
	return ErrDatabus
}

func (ctr *Databus) Out() (data interface{}, err error) {
	if ctr.Available {
		select {
		case data := <-ctr.out:
			return data, err
		case <-ctr.close:
			ctr.Close()
		case <-time.NewTimer(DatabusTimeout).C:
			ctr.Close()
		}
	}
	return data, ErrDatabus
}

func (ctr *Databus) Close() {
	ctr.Available = false
	utils.SafeChanClosure(ctr.in)
	utils.SafeChanClosure(ctr.out)
	utils.SafeChanClosure(ctr.close)
}
