package main

import "go.uber.org/zap"

func handleServiceManage(s Service) {
	if err := s.RunNewSlave(); err != nil {
		s.GetLog().Error(failedConnToManage, zap.Error(err))
	}
}
