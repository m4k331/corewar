package syncd

import "sync"

type Queue struct {
	q []interface{}
	sync.RWMutex
}

func NewQueue(size int) *Queue {
	return &Queue{q: make([]interface{}, 0, size)}
}

func (q *Queue) Push(val interface{}) {
	q.Lock()
	q.q = append(q.q, val)
	q.Unlock()
}

func (q *Queue) Pop() (val interface{}) {
	q.Lock()
	if len(q.q) > 0 {
		val = q.q[0]
		q.q = q.q[1:]
	}
	q.Unlock()
	return val
}

func (q *Queue) Len() int {
	q.RLock()
	ln := len(q.q)
	q.RUnlock()
	return ln
}
