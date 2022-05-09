#include <include/core/Simplex.hpp>

namespace rss
{
    Simplex::Simplex()
    {
        vertices.assign(3, Vec2(0, 0));
    }

    Simplex::Simplex(Vec2 a, Vec2 b, Vec2 c)
    {
        vertices.assign(3, Vec2(0, 0));
        
        vertices[0] = a;
        vertices[1] = b;
        vertices[2] = c;
    }

    Simplex::Simplex(Vec2 vertices[3])
    {
        (this->vertices).assign(3, Vec2(0, 0));

        this->vertices[0] = vertices[0];
        this->vertices[1] = vertices[1];
        this->vertices[2] = vertices[2];
    }
}