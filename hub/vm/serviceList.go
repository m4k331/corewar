package main

import (
	"sync"
	"sync/atomic"
)

// it's fast if not a cache contention
type ServicesList struct {
	mx sync.RWMutex
	m  map[string]*Service
	n  *int32
}

func NewServiceList(size int) *ServicesList {
	return &ServicesList{
		m: make(map[string]*Service, size),
		n: new(int32),
	}
}

func (srvList *ServicesList) Load(addr string) (*Service, bool) {
	srvList.mx.RLock()
	srv, ok := srvList.m[addr]
	srvList.mx.RUnlock()
	return srv, ok
}

func (srvList *ServicesList) Store(addr string, srv *Service) {
	srvList.mx.Lock()
	srvList.m[addr] = srv
	atomic.AddInt32(srvList.n, 1)
	srvList.mx.Unlock()
}

func (srvList *ServicesList) Delete(addr string) {
	srvList.mx.Lock()
	delete(srvList.m, addr)
	atomic.AddInt32(srvList.n, -1)
	srvList.mx.Unlock()
}

func (srvList *ServicesList) Len() int {
	return int(atomic.LoadInt32(srvList.n))
}
