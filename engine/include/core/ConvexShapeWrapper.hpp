#ifndef __CONVEX_SHAPE_WRAPPER__
#define __CONVEX_SHAPE_WRAPPER__

#include <include/core/ConvexShape.hpp>
#include <include/core/Angle.hpp>
#include <include/core/Vec2.hpp>
#include <iostream>

namespace rss
{
    class ConvexShapeWrapper
    {
    public:
        std::shared_ptr<ConvexShape> ptr;

        Angle angle;
        Vec2 offset;

        AABB aabb;

        ConvexShapeWrapper(std::shared_ptr<ConvexShape> ptr, Angle angle, Vec2 offset);
        Vec2 getFarthestPointInDirection(Vec2 direction);
        void updateAABB();

        ConvexShapeWrapper(const ConvexShapeWrapper&) = default;	
    };
}

#endif