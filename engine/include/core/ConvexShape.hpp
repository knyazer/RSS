#ifndef __CONVEX_SHAPE_HPP__
#define __CONVEX_SHAPE_HPP__

#include <include/core/Vec2.hpp>
#include <include/core/AABB.hpp>
#include <include/core/Angle.hpp>

namespace rss
{
    class ConvexShape
    {
        public:
            virtual Vec2 getFarthestPointInDirection(Vec2 direction);
            virtual void updateAABB(Vec2 offset, Angle angle);
            virtual void updateArea();
            virtual Vec2 findCenterOfMass();
            
            AABB aabb;
            double area;

            ~ConvexShape() = default;
    };
}


#endif