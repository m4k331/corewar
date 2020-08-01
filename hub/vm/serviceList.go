package main

import "sync"

// it's fast if not a cache contention
type ServicesList struct {
	mx sync.RWMutex
	m  map[string]*Service
}

func NewServiceList(size int) *ServicesList {
	return &ServicesList{m: make(map[string]*Service, size)}
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
	srvList.mx.Unlock()
}

func (srvList *ServicesList) Delete(addr string) {
	srvList.mx.Lock()
	delete(srvList.m, addr)
	srvList.mx.Unlock()
}
