package main

import (
	"bytes"
	"gopkg.in/yaml.v3"
	"net"
	"os"
	"time"
)

type Config struct {
	ServiceManage struct {
		Addr        string `yaml:"address"`
		TCPSettings `yaml:"tcp_settings"`
	} `yaml:"service_manage"`

	ServiceVM struct {
		TCPSettings `yaml:"tcp_settings"`
	} `yaml:"service_vm"`

	ServiceASM struct {
		TCPSettings `yaml:"tcp_settings"`
	} `yaml:"service_asm"`
}

func NewConfig(path string) (*Config, error) {
	file, err := os.Open(path)
	if err != nil {
		return nil, err
	}
	defer func() {
		_ = file.Close()
	}()

	data := new(bytes.Buffer)
	_, err = data.ReadFrom(file)
	if err != nil {
		return nil, err
	}

	conf := new(Config)
	err = yaml.Unmarshal(data.Bytes(), conf)
	return conf, err
}

type TCPSettings struct {
	ReadDeadline    int  `yaml:"read_deadline_second"`
	WriteDeadline   int  `yaml:"write_deadline_second"`
	Deadline        int  `yaml:"deadline_second"`
	KeepAlivePeriod int  `yaml:"keep_alive_period_second"`
	KeepAlive       bool `yaml:"keep_alive"`
}

func (set TCPSettings) ApplyDeadlineToListener(listen *net.TCPListener) (e error) {
	if set.Deadline > 0 {
		t := time.Now()
		t.Add(time.Second * time.Duration(set.Deadline))
		e = listen.SetDeadline(t)
	}
	return e
}

func (set TCPSettings) ApplyReadDeadlineToConnection(conn *net.TCPConn) (e error) {
	if set.ReadDeadline > 0 {
		t := time.Now()
		t.Add(time.Second * time.Duration(set.ReadDeadline))
		e = conn.SetReadDeadline(t)
	}
	return e
}

func (set TCPSettings) ApplyWriteDeadlineToConnection(conn *net.TCPConn) (e error) {
	if set.ReadDeadline > 0 {
		t := time.Now()
		t.Add(time.Second * time.Duration(set.WriteDeadline))
		e = conn.SetWriteDeadline(t)
	}
	return e
}

func (set TCPSettings) ApplyToConnection(conn *net.TCPConn) (e error) {
	if set.KeepAlive {
		if e = conn.SetKeepAlive(true); e != nil {
			return e
		}
		if set.KeepAlivePeriod > 0 {
			if e = conn.SetKeepAlivePeriod(time.Second * time.Duration(set.KeepAlivePeriod)); e != nil {
				return e
			}
		}
	}
	return e
}
