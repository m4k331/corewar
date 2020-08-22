package main

func SafeChanClosure(ch interface{}) {
	loop := true
	switch ch.(type) {
	case chan interface{}:
		c := ch.(chan interface{})
		for loop {
			select {
			case _, ok := <-c:
				if !ok {
					loop = false
				}
			default:
				close(c)
				loop = false
			}
		}
	case chan struct{}:
		c := ch.(chan struct{})
		for loop {
			select {
			case _, ok := <-c:
				if !ok {
					loop = false
				}
			default:
				close(c)
				loop = false
			}
		}
	case chan int:
		c := ch.(chan int)
		for loop {
			select {
			case _, ok := <-c:
				if !ok {
					loop = false
				}
			default:
				close(c)
				loop = false
			}
		}
	}
}
