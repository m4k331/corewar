package main

type PoolMessages map[int]Message

func (pm *PoolMessages) Get(typeMsg int) Message {
	if m, ok := (*pm)[typeMsg]; ok {
		return m
	}
	return nil
}

func NewPoolMessages(serviceType int) *PoolMessages {
	switch serviceType {
	case ServiceTypeVM:
		return &PoolMessages{
			TypeMsgHandshakeVM:      new(HandshakeVM),
			TypeMsgGameNotification: new(GameNotification),
			TypeMsgGameStatus:       new(GameStatus),
			TypeMsgOperation:        new(Operation),
			TypeMsgStatusOfProcess:  new(StatusOfProcess),
			TypeMsgEndOfGame:        new(EndOfGame),
			TypeMsgGamePresentation: new(GamePresentation),
			TypeMsgInitialGame:      new(InitialGame),
			TypeMsgSendBot:          new(BotASM),
		}
	case ServiceTypeASM:
		return &PoolMessages{
			TypeMsgHandshakeASM: new(HandshakeASM),
			TypeMsgErrorASM:     new(ErrorASM),
			TypeMsgBinaryASM:    new(BotASM),
		}
	}
	return &PoolMessages{
		TypeMsgHandshakeVM:  new(HandshakeVM),
		TypeMsgHandshakeASM: new(HandshakeASM),
	}
}
