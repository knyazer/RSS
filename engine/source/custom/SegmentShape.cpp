#include <include/custom/SegmentShape.hpp>

namespace soccer
{
    SegmentShape::SegmentShape()
    {
        position = Vec2(0, 0);
        radius = 0.11;
        mid = 0;
        range = M_PI;
    }

    SegmentShape::SegmentShape(Vec2 position, double radius, Angle mid, Angle range)
    {
        this->position = position;
        this->radius = radius;
        this->mid = mid;
        this->range = range;
    }

    Vec2 SegmentShape::getFarthestPointInDirection(Vec2 direction)
    {
        Angle angle = direction.toAngle();

        if (angle.diff(mid).rad() > range.rad() / 2)
        {
            if ((angle - mid).rad() < M_PI)
                return position + Vec2::fromAngle(mid + range / 2) * radius;
            else 
                return position + Vec2::fromAngle(mid - range / 2) * radius;
        }

        Vec2 farthestPoint = position + direction.norm() * radius;
        return farthestPoint;
    }

    Vec2 SegmentShape::findCenterOfMass()
    {
        return position;
    }

    void SegmentShape::updateArea()
    {
        area = range.rad() * radius * radius / 2;
    }
}