#include <include/core/ConvexShape.hpp>

namespace rss
{
    Vec2 ConvexShape::getFarthestPointInDirection(Vec2 direction)
    {
        return Vec2(0, 0);
    }

    void ConvexShape::updateAABB(Vec2 offset, Angle angle)
    {
        Vec2    up = getFarthestPointInDirection(Vec2(0, 1).rotate(-angle)).rotate(angle), 
                left = getFarthestPointInDirection(Vec2(-1, 0).rotate(-angle)).rotate(angle), 
                down = getFarthestPointInDirection(Vec2(0, -1).rotate(-angle)).rotate(angle), 
                right = getFarthestPointInDirection(Vec2(1, 0).rotate(-angle)).rotate(angle);

        Vec2 min = offset + Vec2::elementwiseMin(Vec2::elementwiseMin(up, down), Vec2::elementwiseMin(left, right));
        Vec2 max = offset + Vec2::elementwiseMax(Vec2::elementwiseMax(up, down), Vec2::elementwiseMax(left, right));

        aabb.update(min, max);
    }

    Vec2 ConvexShape::findCenterOfMass()
    {
        return Vec2(0, 0);
    }

    void ConvexShape::updateArea()
    {
        area = 0;
    }
}