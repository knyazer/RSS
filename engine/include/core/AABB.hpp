#ifndef __AABB_HPP__
#define __AABB_HPP__

#include <include/core/Vec2.hpp>
#include <include/core/misc.hpp>

namespace rss
{
    struct AABB
    {
        Vec2 min, max;

        inline void update(Vec2 a, Vec2 b)
        {
            min = Vec2(rss::min(a.x, b.x), rss::min(a.y, b.y));
            max = Vec2(rss::max(a.x, b.x), rss::max(a.y, b.y));
        }

        Vec2 mid()
        {
            return (min + max) / 2;
        }

        static bool intersects(AABB &A, AABB &B)
        {
            return  !((A.max.x < B.min.x) ||
                    (A.max.y < B.min.y) ||
                    (A.min.x > B.max.x) ||
                    (A.min.y > B.max.y));
        }

        bool hasInside(Vec2 point)
        {
            return !(max.x < point.x || min.x > point.x || max.y < point.y || min.y > point.y);
        }

        static AABB merge(AABB &A, AABB &B)
        {
            AABB result;

            result.min = Vec2::elementwiseMin(A.min, B.min);
            result.max = Vec2::elementwiseMax(A.max, B.max);

            return result;
        }
    };
}


#endif