package subscribe

import (
	"container/ring"
	"cw/hub/gen"
	"cw/hub/utils"
)

type Ring struct {
	r *ring.Ring
	m map[int]*ring.Ring
	C chan int
}

func NewRing(c chan int) *Ring {
	return &Ring{
		m: make(map[int]*ring.Ring, 8),
		C: c,
	}
}

func (r *Ring) Subscribe() *Subscriber {
	sub := &Subscriber{
		id:    gen.GetIntID(),
		codes: make(chan byte, 100),
		close: r.C,
	}
	e := ring.New(1)
	e.Value = sub
	switch r.r {
	case nil:
		r.r = e
	default:
		r.r.Link(e)
	}
	r.m[sub.id] = e
	return sub
}

func (r *Ring) Unsubscribe(id int) {
	if e, ok := r.m[id]; ok {
		for r.r.Next() != e {
			r.r = r.r.Next()
		}
		delete(r.m, id)
		switch r.r {
		case r.r.Next():
			r.r = nil
		default:
			r.r.Unlink(1)
		}
	}
}

func (r *Ring) UnsubscribeAll() {
	for r.r.Len() > 1 {
		delete(r.m, r.r.Value.(*Subscriber).id)
		r.r.Unlink(1)
	}
	delete(r.m, r.r.Value.(*Subscriber).id)
	r.r = nil
}

func (r *Ring) Notify(id int, code byte) {
	if e, ok := r.m[id]; ok {
		e.Value.(*Subscriber).codes <- code
	}
}

func (r *Ring) NotifyAll(code byte) {
	r.r.Do(func(sub interface{}) {
		sub.(*Subscriber).codes <- code
	})
}

type Subscriber struct {
	id    int
	codes chan byte
	close chan int
}

func (s *Subscriber) Code() <-chan byte {
	return s.codes
}

func (s *Subscriber) Unsubscribe() {
	s.close <- s.id
	utils.SafeChanClosure(s.codes)
}
