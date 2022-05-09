#ifndef __VEC_2__
#define __VEC_2__

#include <cmath>
#include <include/core/misc.hpp>
#include <include/core/Angle.hpp>

namespace rss
{
    // Vector defined in Cartesian system
    struct Vec2
    {
        public:
            double x, y;

            Vec2(double x, double y);
            Vec2(double value);
            Vec2();

            // Sum up vectors
            Vec2 operator+(Vec2 other);
            Vec2 operator-(Vec2 other);
            
            // Scale the vector
            Vec2 operator*(double other);
            Vec2 operator/(double other);

            Vec2& operator-=(const Vec2& other);
            Vec2& operator+=(const Vec2& other);

            bool operator==(Vec2 other);

            Vec2 operator-() const;

            // Some vector-specific operations
            double dot(Vec2 other);
            Vec2 cross(Vec2 other);
            Vec2 negate();
            Vec2 norm();
            double size();
            Vec2 perp();
            Vec2 star();
            bool isZero();
            Vec2 rotate(Angle angle);
            Angle toAngle();
            Vec2 xr();
            Vec2 yr();

            static Vec2 rand1();
            static Vec2 tripleProduct(Vec2 a, Vec2 b, Vec2 c);
            static Vec2 elementwiseMax(Vec2 a, Vec2 b);
            static Vec2 elementwiseMin(Vec2 a, Vec2 b);
            static Vec2 fromAngle(Angle angle);
    };
}

#endif