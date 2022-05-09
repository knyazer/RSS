#include <include/core/Angle.hpp>

namespace rss
{
    Angle::Angle()
    {
        value = 0;
    }

    Angle::Angle(double theta)
    {
        *this = theta;
        norm();
    }

    Angle Angle::diff(Angle other)
    {
        return Angle(min(abs((*this - other).rad()), abs((other - *this).rad())));
    }

    double Angle::radRel()
    {
        double res = rad();

        while (res >= M_PI)
            res -= 2 * M_PI;
        while (res < -M_PI)
            res += 2 * M_PI;

        return res;
    }

    double Angle::rad()
    {
        return value;
    }

    double Angle::deg()
    {
        return rad() * RAD2DEG;
    }

    Angle Angle::operator+(Angle other)
    {
        return Angle(value + other.rad());
    }

    Angle Angle::operator-(Angle other)
    {
        return Angle(value - other.rad());
    }

    Angle Angle::operator-() const
    {
        return Angle(-value);
    }

    Angle Angle::operator*(double factor)
    {
        return Angle(value * factor);
    }

    Angle Angle::operator/(double factor)
    {
        return Angle(value / factor);
    }

    Angle Angle::operator=(Angle other)
    {
        value = other.rad();
        norm();
        return *this;
    }

    Angle& Angle::operator+=(const Angle& other)
    {
        *this = (*this) + other;
        return *this;
    }

    Angle& Angle::operator+=(const double& other)
    {
        value += other;
        norm();

        return *this;
    }

    void Angle::norm()
    {
        while (value >= M_PI * 2)
            value -= 2 * M_PI;
        while (value < 0)
            value += 2 * M_PI;
    }

    Angle Angle::operator=(double other)
    {
        value = other;
        norm();
        return *this;
    }

    double Angle::cos_c()
    {
        return cos(value);
    }

    double Angle::sin_c()
    {
        return sin(value);
    }

    double Angle::tan_c()
    {
        return tan(value);
    }
}