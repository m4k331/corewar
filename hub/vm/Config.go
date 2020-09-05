package main

import (
	"bytes"
	"cw/hub/utils"
	"gopkg.in/yaml.v3"
	"net"
	"os"
	"time"
)

type Config struct {
	ServiceManage ServiceConf `yaml:"service_manage"`
	ServiceVM     ServiceConf `yaml:"service_vm"`
	ServiceASM    ServiceConf `yaml:"service_asm"`
}

type ServiceConf struct {
	Addr        string `yaml:"address,omitempty"`
	MaxNumChild int    `yaml:"max_num_child,omitempty"`
	TCPSettings `yaml:"tcp_settings,omitempty"`
	WorkerConf  `yaml:"worker,omitempty"`
}

type WorkerConf struct {
	TCPSettings `yaml:"tcp_settings,omitempty"`
}

type TCPSettings struct {
	WriteBuffer     int  `yaml:"write_buffer_bytes,omitempty"`
	WriteDeadline   int  `yaml:"write_deadline_second,omitempty"`
	ReadDeadline    int  `yaml:"read_deadline_second,omitempty"`
	KeepAlivePeriod int  `yaml:"keep_alive_period_second,omitempty"`
	Deadline        int  `yaml:"deadline_second,omitempty"`
	KeepAlive       bool `yaml:"keep_alive,omitempty"`
}

func NewConfig(path string) (*Config, error) {
	file, e := os.Open(path)
	if e != nil {
		return nil, e
	}
	defer func() { _ = file.Close() }()

	data := new(bytes.Buffer)
	if _, e = data.ReadFrom(file); e != nil {
		return nil, e
	}

	conf := new(Config)
	e = yaml.Unmarshal(data.Bytes(), conf)
	return conf, e
}

func (settings TCPSettings) ApplyToListener(listener *net.TCPListener) (e error) {
	if settings.Deadline > 0 {
		if e = listener.SetDeadline(utils.GetTimeFromNSecond(settings.Deadline)); e != nil {
			return e
		}
	}
	return e
}

func (settings TCPSettings) ApplyToConnection(conn *net.TCPConn) (e error) {
	if settings.KeepAlive {
		if e = conn.SetKeepAlive(true); e != nil {
			return e
		}
		if settings.KeepAlivePeriod > 0 {
			if e = conn.SetKeepAlivePeriod(time.Second * time.Duration(settings.KeepAlivePeriod)); e != nil {
				return e
			}
		}
	}
	if settings.WriteBuffer > 0 {
		if e = conn.SetWriteBuffer(settings.WriteBuffer); e != nil {
			return e
		}
	}
	if settings.WriteDeadline > 0 {
		if e = conn.SetWriteDeadline(utils.GetTimeFromNSecond(settings.WriteDeadline)); e != nil {
			return e
		}
	}
	if settings.ReadDeadline > 0 {
		if e = conn.SetReadDeadline(utils.GetTimeFromNSecond(settings.ReadDeadline)); e != nil {
			return e
		}
	}
	return e
}
