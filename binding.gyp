{
  'targets': [
    {
      'target_name': 'go-addon',
      'cflags!': [ '-fno-exceptions' ],
      'cflags_cc!': [ '-fno-exceptions' ],
      'sources': [
        'lib/libgo.h',
        'addon.cc'
      ],
      'include_dirs': [
          "<!@(node -p \"require('node-addon-api').include\")"
      ],
      'libraries': [ '../lib/libgo.a' ],
      'dependencies': [
          "<!(node -p \"require('node-addon-api').gyp\")"
      ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }
  ]
}