#ifndef __GJK_HPP__
#define __GJK_HPP__

#include <include/core/Shape.hpp>
#include <include/core/CollisionSimplex.hpp>
#include <include/core/Vec2.hpp>
#include <include/core/outputOverloads.hpp>
#include <include/core/Object.hpp>
#include <iostream>

namespace rss
{
    namespace GJK
    {
        using namespace std;
        
        const int ITERATIONS_LIMIT = 30;

        class PointWrapper : public Vec2
        {
            public:
                PointWrapper(Vec2 value);
                
                AABB aabb;
                Vec2 getFarthestPointInDirection(Vec2 direction);
        };

        // Return Minkowski Difference of passed shapes
        template <typename T1, typename T2>
        Vec2 support(T1 A, T2 B, Vec2 direction)
        {
            return A.getFarthestPointInDirection(direction) - B.getFarthestPointInDirection(direction.negate());
        }

        template <typename T1, typename T2>
        CollisionSimplex getCollisionSimplex(T1 A, T2 B) 
        {
            size_t index = 0; // index of current vertex of simplex
            Vec2 a, b, c, d, ao, ab, ac, abperp, acperp, simplex[3];

            // initial direction from the center of 2nd body to the center of the 1st body
            d = A.aabb.mid() - B.aabb.mid();

            // if initial direction is zero – set it to any arbitrary direction
            if ((d.x == 0) && (d.y == 0))
            {
                d.x = (rand()) / (double)(RAND_MAX);
                d.y = (rand()) / (double)(RAND_MAX);
            }
            
            // set the first support as initial point of the new simplex
            a = simplex[0] = support(A, B, d);
            
            if (a.dot(d) <= 0)
                return CollisionSimplex(); // no collision
            
            d = a.negate(); // The next search direction is always towards the origin, so the next search direction is negate(a)
            
            uint64_t i = 0;
            while (true) {
                if (i++ > ITERATIONS_LIMIT)
                {
                    std::cout << "GJK failed" << std::endl;
                    return CollisionSimplex();
                }

                a = simplex[++index] = support(A, B, d);
                
                if (a.dot(d) <= 0)
                    return CollisionSimplex(); // no collision
                
                ao = a.negate(); // from point A to Origin is just negative A
                
                // simplex has 2 points (a line segment, not a triangle yet)
                if (index < 2) {
                    b = simplex[0];
                    ab = b - a; // from point A to B
                    d = Vec2::tripleProduct(ab, ao, ab); // normal to AB towards Origin
                    //d = Vec2(-ab.y, ab.x);
                    if (d.size() == 0)
                        d = ab.perp();
                    continue; // skip to next iteration
                }
                
                b = simplex[1];
                c = simplex[0];
                ab = b - a; // from point A to B
                ac = c - a; // from point A to C
                
                acperp = Vec2::tripleProduct(ab, ac, ac);
                
                if (acperp.dot(ao) >= 0) {
                    d = acperp; // new direction is normal to AC towards Origin

                    // In case first line already passed through origin -> generate arbitrary direction
                    if (d.x == 0 && d.y == 0)
                    {
                        d.x = (rand()) / (double)(RAND_MAX);
                        d.y = (rand()) / (double)(RAND_MAX);
                    }
                } 
                else {
                    abperp = Vec2::tripleProduct(ac, ab, ab);
                    
                    if (abperp.dot(ao) < 0)
                        return CollisionSimplex(simplex); // collision
                    
                    simplex[0] = simplex[1]; // swap first element (point C)

                    d = abperp; // new direction is normal to AB towards Origin
                }
                
                simplex[1] = simplex[2]; // swap element in the middle (point B)
                --index;
            }
            
            return CollisionSimplex();
        }
    }
}


#endif