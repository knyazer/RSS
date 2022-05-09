#ifndef __NAPI_WRAPPERS__
#define __NAPI_WRAPPERS__

#include <include/RSS.hpp>
#include <iostream>
#include <napi.h>

namespace addon
{
    using namespace Napi;

    String wrap(Env& env, std::string str);
    Boolean wrap(Env& env, bool value);
    Number wrap(Env& env, rss::Angle angle);
    Number wrap(Env& env, double x);

    Object wrap(Env& env, rss::Vec2 vec);
    Object wrap(Env& env, rss::AABB aabb);
    Object wrap(Env& env, rss::Shape shape);
    Object wrap(Env& env, rss::Object object);
    Object wrap(Env& env, rss::World world);
}

#endif
