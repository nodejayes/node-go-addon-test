#include <node.h>
#include "lib/libgo.h"

using v8::Exception;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::String;
using v8::Value;

void ProcessMethod  (const FunctionCallbackInfo<Value> &args) {
  Isolate *isolate = args.GetIsolate();

  if (args.Length() < 3) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong number of Arguments")
        .ToLocalChecked()
    ));
    return;
  }

  if (!args[0]->IsString() || !args[1]->IsString() || !args[2]->IsString()) {
    isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "The Argument must be a String")
            .ToLocalChecked()
        ));
        return;
  }

  v8::String::Utf8Value actionNameUtf8(isolate, args[0]);
  v8::String::Utf8Value actionArgsUtf8(isolate, args[1]);
  v8::String::Utf8Value actionConfigUtf8(isolate, args[2]);
  std::string actionName(*actionNameUtf8);
  std::string actionArgs(*actionArgsUtf8);
  std::string actionConfig(*actionConfigUtf8);
  char *res = Process(actionName.c_str(), actionArgs.c_str(), actionConfig.c_str());
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, res).ToLocalChecked());
  delete res;
}

void Init (Local<Object> exports) {
  NODE_SET_METHOD(exports, "process", ProcessMethod);
}

NODE_MODULE(myGoAddon, Init)