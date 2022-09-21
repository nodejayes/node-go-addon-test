const goAddon = require('./build/Release/go-addon')

goAddon.process(
    'greeter',
    JSON.stringify({name:'Markus'}),
    JSON.stringify({}),
).then(console.log).catch(console.error);
