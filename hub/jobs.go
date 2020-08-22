package main

import (
	"corewar/hub/gen"
	"corewar/hub/syncd"
)

const (
	ASMJobType = "asm"
	VMJobType  = "vm"
)

type Job struct {
	Id   int
	Type string
	Body interface{}
	Out  chan interface{}
}

func NewJob(body interface{}, _type string) *Job {
	return &Job{
		Id:   gen.GetIntID(),
		Type: _type,
		Body: body,
		Out:  make(chan interface{}, 1),
	}
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

func (jp *JobPool) Push(job *Job) {
	if b, ok := jp.buckets.Load(job.Type); ok {
		bucket := b.(*JobBucket)
		bucket.Jobs.Push(job)
		return
	}
	bucket := NewJobBucket(job.Type)
	bucket.Jobs.Push(job)
	jp.buckets.Store(job.Type, bucket)
}

func (jp *JobPool) GetNewDa {
	
}
