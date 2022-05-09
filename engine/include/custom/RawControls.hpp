#ifndef __RAW_CONTROLS_HPP__
#define __RAW_CONTROLS_HPP__

#include <include/core/core.hpp>
#include <include/env/env.hpp>

namespace soccer
{
    using namespace rss;

    class RawControls
    {
        public:
            RawControls();
            RawControls(Vec2 velocity, double angularVelocity);

            Vec2 velocity;
            double angularVelocity;

            RawControls(const RawControls&) = default;	
    };
}

#endif