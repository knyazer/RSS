#ifndef __COLLISION_SIMPLEX__
#define __COLLISION_SIMPLEX__

#include <include/core/Simplex.hpp>

namespace rss
{
    class CollisionSimplex
    {
        public:
            Simplex simplex;
            bool exists;

            CollisionSimplex();
            CollisionSimplex(Simplex simplex);
    };
}

#endif