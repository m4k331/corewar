package main

import (
	"cw/hub/gen"
	"cw/hub/syncd"
	"cw/hub/trait"
	"errors"
)

const (
	ASMJobType = "asm"
	VMJobType  = "vm"
)

type Job struct {
	Id    int
	_type string
	Body  interface{}
	Out   chan interface{}
}

func NewJob(_type string, body interface{}) *Job {
	return &Job{
		Id:    gen.GetIntID(),
		_type: _type,
		Body:  body,
		Out:   make(chan interface{}, 1),
	}
}

func (j *Job) Type() string {
	return j._type
}

type JobBucket struct {
	Type    string
	Jobs    *syncd.Queue
	Databus *syncd.Queue
}

func NewJobBucket(_type string) *JobBucket {
	return &JobBucket{
		Type:    _type,
		Jobs:    syncd.NewQueue(8),
		Databus: syncd.NewQueue(8),
	}
}

type JobPool struct {
	buckets *syncd.Map
}

func (jp *JobPool) Run() error {
	return nil
}

func (jp *JobPool) Push(bag trait.BagPoolInterface) (err error) {
	bucket := jp.loadBucket(bag.Type())
	if bucket == nil {
		bucket = NewJobBucket(bag.Type())
		jp.buckets.Store(bag.Type(), bucket)
	}

	switch bag.(type) {
	case *Job:
		bucket.Jobs.Push(bag.(*Job))
	case trait.Worker:
		bucket.Databus.Push(bag.(trait.Worker))
	default:
		err = errors.New("undefined bag")
	}
	return err
}

func (jp *JobPool) loadBucket(_type string) *JobBucket {
	if bucket, ok := jp.buckets.Load(_type); ok {
		return bucket.(*JobBucket)
	}
	return nil
}

func (jp *JobPool) popDatabus(_type string) *Databus {
	bucket := jp.loadBucket(_type)
	if bucket != nil && bucket.Databus.Len() > 0 {
		return bucket.Databus.Pop().(*Databus)
	}
	return nil
}

func (jp *JobPool) popJob(_type string) *Job {
	bucket := jp.loadBucket(_type)
	if bucket != nil && bucket.Jobs.Len() > 0 {
		return bucket.Jobs.Pop().(*Job)
	}
	return nil
}
