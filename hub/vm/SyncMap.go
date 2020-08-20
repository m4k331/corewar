package main

import (
	"sync"
	"sync/atomic"
)

// TODO: change interface{} to ServiceInterface
// it's fast if not a cache contention else use sync.Map
type SyncMap struct {
	mx sync.RWMutex
	m  map[string]interface{}
	n  *int32
}

func NewSyncMap(size int) *SyncMap {
	return &SyncMap{
		m: make(map[string]interface{}, size),
		n: new(int32),
	}
}

func (syncm *SyncMap) Delete(key string) {
	syncm.mx.Lock()
	delete(syncm.m, key)
	atomic.AddInt32(syncm.n, -1)
	syncm.mx.Unlock()
}

func (syncm *SyncMap) Load(key string) (value interface{}, ok bool) {
	syncm.mx.RLock()
	value, ok = syncm.m[key]
	syncm.mx.RUnlock()
	return value, ok
}

func (syncm *SyncMap) Store(key string, value interface{}) {
	syncm.mx.Lock()
	syncm.m[key] = value
	atomic.AddInt32(syncm.n, 1)
	syncm.mx.Unlock()
}

func (syncm *SyncMap) Len() int {
	return int(atomic.LoadInt32(syncm.n))
}

func (syncm *SyncMap) GetMap() map[string]interface{} {
	return syncm.m
}
