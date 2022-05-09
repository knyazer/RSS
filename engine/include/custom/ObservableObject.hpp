#ifndef __OBSERVABLE_OBJECT_HPP__
#define __OBSERVABLE_OBJECT_HPP__

#include <include/core/core.hpp>

namespace soccer
{
    using namespace rss;

    class ObservableObject
    {
        public:
            Vec2 position;
            Vec2 instantVelocity;
            Vec2 avgVelocity;
            bool ghost;

            ObservableObject();
            void update(Object object, double dt);
            void setup(Object object);
    };
}

#endif