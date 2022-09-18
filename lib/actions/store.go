package actions

type (
	IAction interface {
		Run(string, Config) (string, error)
	}
	Config interface{}
)

var Store = map[string]IAction{
	"greeter": NewGreeter(),
}
