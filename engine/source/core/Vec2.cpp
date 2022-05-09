#include <include/core/Vec2.hpp>

namespace rss
{
    Vec2::Vec2(double x, double y)
    {
        this->x = x;
        this->y = y;
    }

    Vec2::Vec2(double value)
    {
        x = value;
        y = value;
    }

    Vec2::Vec2()
    {
        x = 0;
        y = 0;
    }

    Vec2 Vec2::operator+(Vec2 other)
    {
        return Vec2(x + other.x, y + other.y);
    }

    Vec2 Vec2::operator-(Vec2 other)
    {
        return Vec2(x - other.x, y - other.y);
    }

    Vec2 Vec2::operator-() const
    {
        return Vec2(-x, -y);
    }

    Vec2 Vec2::operator*(double other)
    {
        return Vec2(x * other, y * other);
    }

    Vec2 Vec2::operator/(double other)
    {
        return Vec2(x / other, y / other);
    }

    bool Vec2::operator==(Vec2 other)
    {
        return x == other.x && y == other.y;
    }

    Vec2& Vec2::operator+=(const Vec2& other)
    {
        x += other.x;
        y += other.y;

        return *this;
    }

    Vec2& Vec2::operator-=(const Vec2& other)
    {
        x -= other.x;
        y -= other.y;

        return *this;
    }

    double Vec2::dot(Vec2 other)
    {
        return x * other.x + y * other.y;
    }

    Vec2 Vec2::star()
    {
        return Vec2(-y, x);
    }

    Vec2 Vec2::negate()
    {
        return Vec2(-x, -y);
    }

    double Vec2::size()
    {
        return sqrt(x * x + y * y);
    }

    Vec2 Vec2::norm()
    {
        double magnitude = size();
        if (magnitude == 0)
            return Vec2(1, 0);
        
        return *this / magnitude;
    }

    Vec2 Vec2::rand1()
    {
        return Vec2(randf(), randf());
    }

    Vec2 Vec2::tripleProduct(Vec2 a, Vec2 b, Vec2 c)
    {
        return b * a.dot(c) - a * b.dot(c);
    }

    Vec2 Vec2::perp()
    {
        return Vec2(-y, x);
    }

    bool Vec2::isZero()
    {
        return x == 0 && y == 0;
    }

    Vec2 Vec2::elementwiseMin(Vec2 a, Vec2 b)
    {
        return Vec2(min(a.x, b.x), min(a.y, b.y));
    }

    Vec2 Vec2::elementwiseMax(Vec2 a, Vec2 b)
    {
        return Vec2(max(a.x, b.x), max(a.y, b.y));
    }

    Vec2 Vec2::rotate(Angle angle)
    {
        return Vec2(
            x * angle.cos_c() - y * angle.sin_c(),
            x * angle.sin_c() + y * angle.cos_c()
        );
    }

    Vec2 Vec2::fromAngle(Angle angle)
    {
        return Vec2(angle.cos_c(), angle.sin_c());
    }

    Angle Vec2::toAngle()
    {
        return Angle(atan2(y, x));
    }

    Vec2 Vec2::xr()
    {
        return Vec2(-x, y);
    }

    Vec2 Vec2::yr()
    {
        return Vec2(x, -y);
    }
}