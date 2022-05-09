#include <include/core/GJK.hpp>

namespace rss
{
    GJK::PointWrapper::PointWrapper(Vec2 value)
    {
        x = value.x;
        y = value.y;

        aabb.update(value, value);
    }

    Vec2 GJK::PointWrapper::getFarthestPointInDirection(Vec2 direction)
    {
        return *this;
    }
}