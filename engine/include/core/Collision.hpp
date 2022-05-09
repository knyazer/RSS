#ifndef __COLLISION_HPP__
#define __COLLISION_HPP__

#include <include/core/Object.hpp>
#include <include/core/Shape.hpp>
#include <include/core/Vec2.hpp>
#include <include/core/GJK.hpp>
#include <include/core/EPA.hpp>
#include <include/core/ConvexShapeWrapper.hpp>

namespace rss
{
    namespace Collision
    {
        template <typename T1, typename T2>
        Vec2 getPenetrationVector(T1 A, T2 B)
        {
            CollisionSimplex collision = GJK::getCollisionSimplex(A, B);

            if (collision.exists)
            {
                Vec2 penetrationVector = EPA::expand(A, B, collision.simplex);
                return penetrationVector;// + penetrationVector.norm() * EPA::RESOLVE_OFFSET;
            }
            
            return Vec2(0, 0);
        }

        template <typename T1, typename T2>
        bool exists(T1 A, T2 B)
        {
            return GJK::getCollisionSimplex(A, B).exists;
        }
    }
}

#endif