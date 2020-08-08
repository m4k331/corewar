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
			TypeMsgHeader:      NewHeader(b),
			TypeMsgHandshakeVM: NewHandshake(b),
			//TypeMsgGameNotification: &GameNotification{buff: b},
			//TypeMsgGameStatus:       &GameStatus{buff: b},
			//TypeMsgOperation:        &Operation{buff: b},
			//TypeMsgStatusOfProcess:  &StatusOfProcess{buff: b},
			//TypeMsgEndOfGame:        &EndOfGame{buff: b},
			//TypeMsgGamePresentation: &GamePresentation{buff: b},
			//TypeMsgInitialGame:      &InitialGame{buff: b},
			//TypeMsgSendBot:          &BotASM{buff: b},
		}
	case ServiceTypeASM:
		return &PoolMessages{
			TypeMsgHeader:       NewHeader(b),
			TypeMsgHandshakeASM: NewHandshake(b),
			TypeMsgErrorASM:     NewErrorASM(b),
			TypeMsgBinaryASM:    NewBotASM(b),
		}
	}
	return &PoolMessages{
		TypeMsgHeader:       NewHeader(b),
		TypeMsgHandshakeVM:  NewHandshake(b),
		TypeMsgHandshakeASM: NewHandshake(b),
	}
}
