#ifndef __SEGMENT_SHAPE_HPP__
#define __SEGMENT_SHAPE_HPP__

#include <include/core/core.hpp>

namespace soccer
{
    using namespace rss;
    
    class SegmentShape : public ConvexShape
    {
        public:
            Vec2 position;
            double radius;
            Angle mid, range;

            SegmentShape(Vec2 position, double radius=0.11, Angle mid=0, Angle range=M_PI);
            SegmentShape();

            Vec2 getFarthestPointInDirection(Vec2 direction);

            void updateArea();
            Vec2 findCenterOfMass();

            SegmentShape(const SegmentShape&) = default;
    };
}

#endif