#ifndef __SHAPE_HPP__
#define __SHAPE_HPP__

#include <vector>
#include <stdexcept>
#include <memory>
#include <iostream>
#include <include/core/ConvexShape.hpp>
#include <include/core/Vec2.hpp>
#include <include/core/Angle.hpp>

namespace rss
{
    class Shape
    {
        public:
            std::vector<std::shared_ptr<ConvexShape>> parts;
            AABB aabb;
            Vec2 centerOfMass;

            template <class T>
            Shape(T shape)
            {
                parts.push_back(std::shared_ptr<ConvexShape>(new T(shape)));
            }

            template <class T>
            void add(T shape)
            {
                parts.push_back(std::shared_ptr<ConvexShape>(new T(shape)));
            }

            void updateAABB(Vec2 offset, Angle angle);

            Shape();

            Vec2 getFarthestPointInDirection(Vec2 direction);
            Vec2 findCenterOfMass();
            void finalize();

            Shape(const Shape&) = default;	
    };
}


#endif