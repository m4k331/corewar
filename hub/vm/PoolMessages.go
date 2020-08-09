package main

const defaultPoolMessageSize = 8218

type PoolMessages map[int]Message

func (pm *PoolMessages) Get(typeMsg int) Message {
	if m, ok := (*pm)[typeMsg]; ok {
		return m
	}
	return nil
}

func NewPoolMessages(serviceType int) *PoolMessages {
	var b = NewBufferMessage(defaultPoolMessageSize)

	switch serviceType {
	case ServiceTypeVM:
		return &PoolMessages{
			TypeMsgHeader:           NewHeader(b),
			TypeMsgHandshakeVM:      NewHandshake(b),
			TypeMsgGameNotification: NewGameNotification(b),
			TypeMsgGameStatus:       NewGameStatus(b),
			TypeMsgOperation:        NewOperation(b),
			TypeMsgStatusOfProcess:  NewStatusOfProcess(b),
			TypeMsgEndOfGame:        NewEndOfGame(b),
			TypeMsgGamePresentation: NewGamePresentation(b),
			TypeMsgInitialGame:      NewInitialGame(b),
			TypeMsgBotASM:           NewBotASM(b),
		}
	case ServiceTypeASM:
		return &PoolMessages{
			TypeMsgHeader:       NewHeader(b),
			TypeMsgHandshakeASM: NewHandshake(b),
			TypeMsgErrorASM:     NewErrorASM(b),
			TypeMsgBotASM:       NewBotASM(b),
		}
	}
	return &PoolMessages{
		TypeMsgHeader:       NewHeader(b),
		TypeMsgHandshakeVM:  NewHandshake(b),
		TypeMsgHandshakeASM: NewHandshake(b),
	}
}
