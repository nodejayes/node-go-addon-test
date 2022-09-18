package main

/*
#include<stdbool.h>
typedef const char cchar_t;
*/
import "C"
import (
	"encoding/json"
	"fmt"
	"github.com/nodejayes/node-go-addon-test/lib/actions"
)

//export Process
func Process(action *C.cchar_t, arguments *C.cchar_t, config *C.cchar_t) *C.char {
	a := actions.Store[C.GoString(action)]
	if a == nil {
		return C.CString(`{"error":"action not exists"}`)
	}
	var c actions.Config
	err := json.Unmarshal([]byte(C.GoString(config)), &c)
	if err != nil {
		return C.CString(fmt.Sprintf(`{"error":"%v"}`, err.Error()))
	}
	res, err := a.Run(C.GoString(arguments), c)
	if err != nil {
		return C.CString(fmt.Sprintf(`{"error":"%v"}`, err.Error()))
	}
	return C.CString(res)
}

// required to build
func main() {}
