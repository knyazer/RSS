#ifndef __ANGLE_HPP__
#define __ANGLE_HPP__

#include <cmath>
#include <include/core/misc.hpp>
#include <memory>

#ifndef M_PI
#define M_PI 3.141592
#endif

#define M_PI 3.141592

namespace rss
{
    class Angle
    {
        private:
            double value;
        
        public:
            static constexpr double PI = M_PI;
            static constexpr double PI2 = PI * 2;
            static constexpr double RAD2DEG = 180.0 / PI;
            static constexpr double DEG2RAD = PI / 180.0;

            Angle();
            Angle(double theta);

            Angle diff(Angle other);

            double rad();
            double deg();
            double radRel();
            void norm();

            Angle operator+(Angle other);
            Angle operator-(Angle other);
            Angle operator*(double factor);
            Angle operator/(double factor);

            Angle operator-() const;
            
            Angle operator=(Angle other);
            Angle operator=(double other);

            Angle& operator+=(const Angle& other);
            Angle& operator+=(const double& other);

            double cos_c();
            double sin_c();
            double tan_c();
    };
}

#endif