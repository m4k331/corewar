package trait

type Worker interface {
	Run() error
	Stop()
	Subscribe() *Subscriber
	GetIN() chan<- interface{}
	GetOUT() <-chan interface{}
}
