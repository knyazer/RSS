#include <include/core/ConvexShapeWrapper.hpp>

namespace rss
{
    ConvexShapeWrapper::ConvexShapeWrapper(std::shared_ptr<ConvexShape> ptr, Angle angle, Vec2 offset)
    {
        this->ptr = ptr;
        this->angle = angle;
        this->offset = offset;

        updateAABB();
    }
    
    Vec2 ConvexShapeWrapper::getFarthestPointInDirection(Vec2 direction)
    {
        return offset + ptr->getFarthestPointInDirection(direction.rotate(-angle)).rotate(angle); // SAME 1
    }

    void ConvexShapeWrapper::updateAABB() // SAME 2
    {
        Vec2    up = getFarthestPointInDirection(Vec2(0, 1)), 
                left = getFarthestPointInDirection(Vec2(-1, 0)), 
                down = getFarthestPointInDirection(Vec2(0, -1)), 
                right = getFarthestPointInDirection(Vec2(1, 0));

        Vec2 min = Vec2::elementwiseMin(Vec2::elementwiseMin(up, down), Vec2::elementwiseMin(left, right));
        Vec2 max = Vec2::elementwiseMax(Vec2::elementwiseMax(up, down), Vec2::elementwiseMax(left, right));

        aabb.update(min, max);
    }
}