#include <include/core/CollisionSimplex.hpp>

namespace rss
{
    CollisionSimplex::CollisionSimplex()
    {
        exists = false;
    }

    CollisionSimplex::CollisionSimplex(Simplex simplex)
    {
        exists = true;
        this->simplex = simplex;
    }
}