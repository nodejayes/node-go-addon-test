const goAddon = require('./build/Release/go-addon')

console.log(goAddon.process(
    'greeter',
    JSON.stringify({name:'Markus'}),
    JSON.stringify({},
)))