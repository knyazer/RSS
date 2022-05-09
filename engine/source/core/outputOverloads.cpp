#include <include/core/outputOverloads.hpp>

namespace rss
{
    std::ostream &operator<<(std::ostream &os, Vec2 const &m) 
    { 
        return os << "Vec2(" << m.x << ", " << m.y << ")";
    }

    std::ostream &operator<<(std::ostream &os, Circle const &m) 
    { 
        return os << "Circle(" << m.radius << ", " << m.position << ")";
    }
}