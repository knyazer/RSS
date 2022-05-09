#ifndef __SIMPLEX_HPP__
#define __SIMPLEX_HPP__

#include <vector>
#include <include/core/Vec2.hpp>

namespace rss
{
    class Simplex
    {
        public:
            static const int size = 3;

            std::vector<Vec2> vertices;
            
            Simplex();
            Simplex(Vec2 a, Vec2 b, Vec2 c);
            Simplex(Vec2* vertices); // Size 3 required!

            Vec2& operator [](size_t i) {   return vertices[i];   };
    };
}

#endif