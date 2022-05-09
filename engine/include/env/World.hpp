#ifndef __RESOLVER_HPP__
#define __RESOLVER_HPP__

#include <vector>
#include <include/core/core.hpp>
#include <include/core/Object.hpp>
#include <iostream>
#include <string>

namespace rss
{
    class World
    {
        public:
            std::vector<Object> objects;
            double dt = 0.001;

            World();

            void step();
            void resolveForConvexShapes(Object &A, size_t shapeA, Object &B, size_t shapeB);
            void resolveForObjects(Object &A, Object &B);
            void resolve();
            
            Object& getObjectByName(std::string name);
    };
}

#endif