#ifndef __ADDON__
#define __ADDON__

#define NAPI_CPP_EXCEPTIONS

#include <iostream>
#include <include/RSS.hpp>
#include <include/NapiWrappers.hpp>
#include <napi.h>
#include <cmath>
#include <vector>

#ifndef M_PI
#define M_PI 3.141592
#endif

namespace addon
{
    using namespace Napi;

    soccer::Environment environment;

    Value reset(const CallbackInfo& info);
    Value step(const CallbackInfo& info);
    Object observe(const CallbackInfo& info);
    Object shape(const CallbackInfo& info);

    Object Init(Env env, Object exports);
    NODE_API_MODULE(addon, Init);
}

#endif