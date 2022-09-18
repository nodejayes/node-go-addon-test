package actions

import (
	"encoding/json"
	"fmt"
)

type (
	Greeter         struct{}
	GreeterArgument struct {
		Name string `json:"name"`
	}
)

func NewGreeter() *Greeter {
	return &Greeter{}
}

func (g *Greeter) Run(args string, config Config) (string, error) {
	var arguments GreeterArgument
	err := json.Unmarshal([]byte(args), &arguments)
	if err != nil {
		return "null", err
	}
	return fmt.Sprintf("Hello, %v!", arguments.Name), nil
}
