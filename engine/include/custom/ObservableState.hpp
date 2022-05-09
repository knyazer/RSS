#ifndef __OBSERVABLE_STATE_HPP__
#define __OBSERVABLE_STATE_HPP__

#include <include/core/core.hpp>
#include <include/env/env.hpp>

namespace soccer
{
    using namespace rss;

    class ObservableState
    {
        public:
            struct {
                Vec2 position;
            } ball;

            struct {
                Vec2 position;
                Angle angle;
            } robot;

            ObservableState(World world);
    };
}

#endif