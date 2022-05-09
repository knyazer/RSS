#ifndef __OUTPUT_OVERLOADS__
#define __OUTPUT_OVERLOADS__

#include <iostream>
#include <include/core/Vec2.hpp>
#include <include/core/Circle.hpp>

namespace rss
{
    std::ostream &operator<<(std::ostream &os, Vec2 const &m);
    std::ostream &operator<<(std::ostream &os, Circle const &m);
}

#endif