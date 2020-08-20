package gen

import (
	"strconv"
	"sync/atomic"
)

var gid = new(int64)

func GetStringID() string {
	id := atomic.AddInt64(gid, 1)
	return strconv.Itoa(int(id))
}
