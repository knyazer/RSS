#ifndef __RECT_HPP__
#define __RECT_HPP__

#include <include/core/Vec2.hpp>
#include <include/core/Angle.hpp>
#include <include/core/Polygon.hpp>

namespace rss
{
    class Rect : public Polygon
    {
        public:
            Vec2 min, max;

            Rect();
            Rect(Vec2 min, Vec2 max);

            Rect(const Rect&) = default;	
    };
}

#endif