#ifndef __POLYGON_HPP__
#define __POLYGON_HPP__

#include <vector>
#include <stdexcept>
#include <include/core/Vec2.hpp>
#include <include/core/ConvexShape.hpp>
#include <include/core/misc.hpp>
#include <algorithm>

namespace rss
{
    class Polygon : public ConvexShape
    {
        public:
            std::vector<Vec2> vertices;

            Polygon();
            Polygon(std::vector<Vec2> vertices);

            void setVertices(std::vector<Vec2> vertices);
            Vec2 getFarthestPointInDirection(Vec2 direction);
            Vec2 findCenterOfMass();
            bool isWindingLeft();
            void updateArea();
            double getSignedArea();

            Polygon(const Polygon&) = default;	
    };
}


#endif