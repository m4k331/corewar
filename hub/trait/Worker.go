package trait

import "cw/hub/subscribe"

type Worker interface {
	Run() error
	Stop()
	Subscribe() *subscribe.Subscriber
	GetIN() chan<- interface{}
	GetOUT() <-chan interface{}
}
