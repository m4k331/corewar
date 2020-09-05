package subscribe

import (
	"math/rand"
	"testing"
)

func TestRing_Subscribe(t *testing.T) {
	const N = 100
	c := make(chan int, N)
	r := NewRing(c)
	ss := make([]*Subscriber, 0, N)
	for i := 0; i < N; i++ {
		ss = append(ss, r.Subscribe())
	}
	if len(ss) != r.r.Len() {
		t.Errorf("Bad len Ring [got: %d, expect:%d]\n", r.r.Len(), len(ss))
	}
}

func TestRing_Notify(t *testing.T) {
	const N = 100
	c := make(chan int, N)
	r := NewRing(c)
	ss := make([]*Subscriber, 0, N)
	for i := 0; i < N; i++ {
		ss = append(ss, r.Subscribe())
	}
	for i := 0; i < N; i++ {
		id := ss[i].id
		code := byte(rand.Intn(N))
		r.Notify(id, code)
		got := <-ss[i].Code()
		if code != got {
			t.Errorf("Code [got: %d, expect: %d]\n", got, code)
		}
	}
}

func TestRing_NotifyAll(t *testing.T) {
	const N = 100
	c := make(chan int, N)
	r := NewRing(c)
	ss := make([]*Subscriber, 0, N)
	for i := 0; i < N; i++ {
		ss = append(ss, r.Subscribe())
	}
	r.NotifyAll(N)
	for i := 0; i < N; i++ {
		got := <-ss[i].Code()
		if got != N {
			t.Errorf("Code [got: %d, expect: %d]\n", got, N)
		}
	}
}

func TestRing_Unsubscribe100(t *testing.T) {
	const N = 100
	c := make(chan int, N)
	r := NewRing(c)
	ss := make([]*Subscriber, 0, N)
	for i := 0; i < N; i++ {
		ss = append(ss, r.Subscribe())
	}
	k := rand.Intn(N)
	id := ss[k].id
	r.Unsubscribe(id)
	if len(ss)-1 != r.r.Len() {
		t.Errorf("Bad len Ring [got: %d, expect: %d]\n", r.r.Len(), len(ss)-1)
	}
	fail := false
	r.r.Do(func(sub interface{}) {
		if sub.(*Subscriber).id == id {
			fail = true
		}
	})
	if fail {
		t.Errorf("ID: %d don't deleted :c\n", id)
	}
}

func TestRing_Unsubscribe(t *testing.T) {
	const N = 100
	c := make(chan int, N)
	r := NewRing(c)
	s := r.Subscribe()
	r.Unsubscribe(s.id)
	if r.r.Len() != 0 {
		t.Errorf("Bad len Ring [got: %d, expect: %d]\n", r.r.Len(), 0)
	}
}

func TestRing_UnsubscribeAll(t *testing.T) {
	const N = 100
	c := make(chan int, N)
	r := NewRing(c)
	ss := make([]*Subscriber, 0, N)
	for i := 0; i < N; i++ {
		ss = append(ss, r.Subscribe())
	}
	r.UnsubscribeAll()
	if r.r.Len() != 0 {
		t.Errorf("Bad len Ring [got: %d, expect: %d]\n", r.r.Len(), 0)
	}
}

func TestSubscriber_Code(t *testing.T) {
	const N = 100
	c := make(chan int, N)
	r := NewRing(c)
	s := r.Subscribe()
	r.Notify(s.id, N)
	got := <-s.Code()
	if got != N {
		t.Errorf("Code [got: %d, expect: %d]\n", got, N)
	}
}

func TestSubscriber_Unsubscribe(t *testing.T) {
	const N = 100
	c := make(chan int, N)
	r := NewRing(c)
	ss := make([]*Subscriber, 0, N)
	for i := 0; i < N; i++ {
		ss = append(ss, r.Subscribe())
	}
	k := rand.Intn(N)
	id := ss[k].id
	ss[k].Unsubscribe()
	got := <-c
	if got != id {
		t.Errorf("Close channel error!!! ID [got:%d, expect:%d]\n", got, id)
	}
}

func TestNewRing(t *testing.T) {
	if NewRing(make(chan int, 100)) == nil {
		t.Errorf("Return nil? O_o")
	}
}
