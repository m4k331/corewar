package main

import "go.uber.org/zap"

// TODO: move all consts description to a separate file
const (
	failedCreateNewService = "Failed to create a new Service"
	successConnToWorker    = "RemoteService connected to Worker"
)

func handleWorker(s Service) {
	go func() {
		conn, e := s.GetListener().AcceptTCP()
		if e != nil {
			s.GetLog().Error(failedCreateNewConn,
				zap.String("addr", s.GetAddr()),
				zap.Error(e),
			)
			s.Stop()
			return
		}
		if e = s.GetConfig().(*WorkerConf).ApplyToConnection(conn); e != nil {
			s.GetLog().Error(failApplyTCPSetting,
				zap.String("addr", s.GetAddr()),
				zap.Error(e),
			)
		}
		_ = s.GetListener().Close()

		// TODO: handler
		srv, e := NewRemoteService(s, conn, nil)
		if e != nil {
			s.GetLog().Error(failedCreateNewService,
				zap.String("addr", s.GetAddr()),
				zap.Error(e),
			)
			s.Stop()
			return
		}

		s.GetSlaves().Store(srv.GetAddr(), srv)
		s.GetLog().Info(addedNewService,
			zap.String("addr", srv.GetAddr()),
		)

		srv.Run()
		s.GetLog().Info(successConnToWorker,
			zap.String("addr", srv.GetAddr()),
		)
	}()
}
