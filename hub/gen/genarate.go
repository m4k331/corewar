package gen

import (
	"strconv"
	"sync/atomic"
)

var (
	strId = new(int64)
	intId = new(int64)
)

func GetStringID() string {
	id := atomic.AddInt64(strId, 1)
	return strconv.Itoa(int(id))
}

func GetIntID() int {
	return int(atomic.AddInt64(intId, 1))
}
