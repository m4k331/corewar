package main

import (
	"bytes"
	"gopkg.in/yaml.v3"
	"net"
	"os"
	"time"
)

// TODO: DELETE!!!
// For local testing...
const (
	ServiceTypeVM  = 1
	ServiceTypeASM = 2
)

type Config struct {
	ServiceManage struct {
		AddrTCP *net.TCPAddr
		TCPSettings
	}
	Service map[int]ServiceConf
}

type ServiceConf struct {
	TCPSettings
}

type TCPSettings struct {
	Deadline        *time.Time
	KeepAlive       bool
	KeepAlivePeriod time.Duration
}

func (set *TCPSettings) FillSettings(raw RawTCPSettings) {
	set.KeepAlive = raw.KeepAlive
	if raw.KeepAlivePeriodSecond > 0 {
		set.KeepAlivePeriod = time.Second * time.Duration(raw.KeepAlivePeriodSecond)
	}
	if raw.DeadlineSecond > 0 {
		t := time.Now()
		t.Add(time.Second * time.Duration(raw.DeadlineSecond))
		set.Deadline = &t
	}
}

func (set TCPSettings) ApplyToListener(listen *net.TCPListener) (e error) {
	if set.Deadline != nil {
		e = listen.SetDeadline(*set.Deadline)
	}
	return e
}

func (set TCPSettings) ApplyToConnection(conn *net.TCPConn) (e error) {
	if set.KeepAlive {
		if e = conn.SetKeepAlive(true); e != nil {
			return e
		}
		if set.KeepAlivePeriod > 0 {
			if e = conn.SetKeepAlivePeriod(set.KeepAlivePeriod); e != nil {
				return e
			}
		}
	}
	return e
}

type RawConfig struct {
	ServiceManage struct {
		Addr           string `yaml:"address"`
		RawTCPSettings `yaml:"tcp_settings"`
	} `yaml:"service_manage"`

	ServiceVM struct {
		RawTCPSettings `yaml:"tcp_settings"`
	} `yaml:"service_vm"`

	ServiceASM struct {
		RawTCPSettings `yaml:"tcp_settings"`
	} `yaml:"service_asm"`
}

type RawTCPSettings struct {
	DeadlineSecond        int  `yaml:"deadline_second"`
	KeepAlive             bool `yaml:"keep_alive"`
	KeepAlivePeriodSecond int  `yaml:"keep_alive_period_second"`
}

func MappingRawToConfig(raw *RawConfig) (c *Config, e error) {
	c = new(Config)
	c.ServiceManage.AddrTCP, e = net.ResolveTCPAddr("tcp", raw.ServiceManage.Addr)
	if e != nil {
		return c, e
	}

	c.Service = make(map[int]ServiceConf, 2)

	// Service Manage
	c.ServiceManage.FillSettings(raw.ServiceManage.RawTCPSettings)

	// Service VM
	settings := TCPSettings{}
	settings.FillSettings(raw.ServiceVM.RawTCPSettings)
	c.Service[ServiceTypeVM] = ServiceConf{settings}

	// Service ASM
	settings = TCPSettings{}
	settings.FillSettings(raw.ServiceASM.RawTCPSettings)
	c.Service[ServiceTypeASM] = ServiceConf{settings}

	return c, e
}

func NewConfig(path string) (*Config, error) {
	file, err := os.Open(path)
	if err != nil {
		return nil, err
	}
	defer file.Close()

	data := new(bytes.Buffer)
	_, err = data.ReadFrom(file)
	if err != nil {
		return nil, err
	}

	raw := new(RawConfig)
	err = yaml.Unmarshal(data.Bytes(), raw)
	if err != nil {
		return nil, err
	}

	config, err := MappingRawToConfig(raw)
	return config, err
}
