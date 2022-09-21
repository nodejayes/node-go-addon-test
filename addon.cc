/*#include <node.h>
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
*/

#include <napi.h>
#include "lib/libgo.h"

Napi::String Greeting(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 3) {
        Napi::TypeError::New(env, "3 Parameter expected").ThrowAsJavaScriptException();
    }

    if (!info[0].IsString()) {
        Napi::TypeError::New(env, "action name required").ThrowAsJavaScriptException();
    }
    if (!info[1].IsString()) {
        Napi::TypeError::New(env, "action parameter required").ThrowAsJavaScriptException();
    }
    if (!info[2].IsString()) {
        Napi::TypeError::New(env, "config required").ThrowAsJavaScriptException();
    }

    std::string actionName = info[0].ToString().Utf8Value();
    std::string actionParameter = info[1].ToString().Utf8Value();
    std::string config = info[2].ToString().Utf8Value();

    char *res = Process(actionName.c_str(), actionParameter.c_str(), config.c_str());

    return Napi::String::New(env, res);
}

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  exports.Set("process", Napi::Function::New(env, Greeting));
  return exports;
}

NODE_API_MODULE(myGoAddon, InitAll)