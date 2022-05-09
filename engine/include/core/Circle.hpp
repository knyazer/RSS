#ifndef __CIRCLE_HPP__
#define __CIRCLE_HPP__

#include <include/core/ConvexShape.hpp>
#include <include/core/Vec2.hpp>
#include <include/core/Angle.hpp>
#include <stdexcept>
#include <iostream>

namespace rss
{
    class Circle : public ConvexShape
    {
        public:
            Vec2 position;
            double radius;

            Circle(double radius, Vec2 position);
            Circle();

            void setRadius(double radius);
            double getRadius();

            void setPosition(Vec2 position);
            Vec2 getPosition();

            Vec2 getFarthestPointInDirection(Vec2 direction);

            void updateAABB(Vec2 offset, Angle angle);
            Vec2 findCenterOfMass();
            void updateArea();

            Circle(const Circle&) = default;	
    };
}


#endif