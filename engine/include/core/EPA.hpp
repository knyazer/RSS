#ifndef __EPA_HPP__
#define __EPA_HPP__

#include <include/core/GJK.hpp>
#include <include/core/Simplex.hpp>
#include <include/core/Vec2.hpp>
#include <include/core/misc.hpp>
#include <include/core/Object.hpp>
#include <iostream>

namespace rss
{
    namespace EPA
    {
        using namespace GJK;

        const double HIGH_TOLERANCE = 1e-4; // 0.1mm seems like an unadequate error
        const double LOW_TOLERANCE = 1e-15;
        const double LOWEST_TOLERANCE = 1e-15; // ~ Precision limit
        const double RESOLVE_OFFSET = 1e-9;
        const int ITERATIONS_LIMIT = 60;

        struct Edge
        {
            double distance;
            int index;
            Vec2 normal;
        };

        Edge findClosestEdgeFast(Simplex simplex, int prevBestIndex);
        Edge findClosestEdgeSlow(Simplex simplex, int prevBestIndex);

        template <typename T1, typename T2>
        Vec2 expand(T1 A, T2 B, Simplex simplex)
        {
            uint64_t i = 0;
            int bestIndex = 1;
            while (true) 
            {
                // obtain the feature (edge for 2D) closest to the 
                // origin on the Minkowski Difference
                Edge e = findClosestEdgeFast(simplex, bestIndex);
                bestIndex = e.index;

                // obtain a new support point in the direction of the edge normal
                Vec2 p = GJK::support(A, B, e.normal);
                // check the distance from the origin to the edge against the
                // distance p is along e.normal
                double d = p.dot(e.normal);

                double error = d - e.distance;

                if (i++ > ITERATIONS_LIMIT)
                {
                    // If error is really bad throw warning and return zero
                    if (error > HIGH_TOLERANCE)
                    {
                        std::cout   << "EPA failed with distance " << d << " and error " << error 
                                    << ", therefore return null. Look in the docs for 'EPA fail'" << std::endl;
                        return Vec2(0, 0);
                    }

                    return e.normal * d;
                }

                if (error < LOW_TOLERANCE) 
                {
                    // the tolerance should be something positive close to zero (ex. 0.00001)

                    // if the difference is less than the tolerance then we can
                    // assume that we cannot expand the simplex any further and
                    // we have our solution

                    return e.normal * d;
                } 
                else 
                    simplex.vertices.insert(simplex.vertices.begin() + e.index, p);
            }
        }
    }
}

#endif