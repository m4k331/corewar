package syncd

import "sync"

// it's fast if not a cache contention else use sync.Map
type Map struct {
	m map[string]interface{}
	sync.RWMutex
}

func NewMap(size int) *Map {
	return &Map{m: make(map[string]interface{}, size)}
}

func (m *Map) Delete(key string) {
	m.Lock()
	delete(m.m, key)
	m.Unlock()
}

func (m *Map) Load(key string) (value interface{}, ok bool) {
	m.RLock()
	value, ok = m.m[key]
	m.RUnlock()
	return value, ok
}

func (m *Map) Store(key string, value interface{}) {
	m.Lock()
	m.m[key] = value
	m.Unlock()
}

func (m *Map) Len() int {
	m.RLock()
	ln := len(m.m)
	m.RUnlock()
	return ln
}

func (m *Map) GetKeys() []string {
	keys := make([]string, 0, len(m.m))
	m.RLock()
	for key := range m.m {
		keys = append(keys, key)
	}
	m.RUnlock()
	return keys
}
