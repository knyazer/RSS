#ifndef __ENVIRONMENT_HPP__
#define __EVNIRONMENT_HPP__

#include <include/core/core.hpp>
#include <include/env/env.hpp>

#include <include/custom/SegmentShape.hpp>
#include <include/custom/RawControls.hpp>
#include <include/custom/ObservableState.hpp>
#include <include/custom/ObservableObject.hpp>

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

namespace soccer
{
    using namespace rss;

    class Environment
    {
        public:
            World world;
            std::map<std::string, double> unghostTimer;
            double time;

            struct
            {
                ObservableObject ball;
                ObservableObject robot;
            } observable;

            void reset();
            void step();
            RawControls control(ObservableState state);
            ObservableState observe(World world);
            void applyControl(Object& object, RawControls controls);

            void noProgressControl();
            void outOfBoundsControl();
            void goalControl();
            void ballSuckingControl();

            Vec2 findNearestEmptyZone(Vec2 position);
    };
}

#endif