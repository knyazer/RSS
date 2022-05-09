#include <include/core/Circle.hpp>

namespace rss
{
    Circle::Circle()
    {
        position = Vec2(0, 0);
        radius = 1;
    }

    Circle::Circle(double radius, Vec2 position)
    {
        this->radius = radius;
        this->position = position;
    }

    void Circle::setRadius(double radius)
    {
        if (radius < 0)
        {
            throw std::invalid_argument("Circle radius must be positive");
            return;
        }
        
        this->radius = radius;
    }

    double Circle::getRadius()
    {
        return radius;
    }

    void Circle::setPosition(Vec2 position)
    {
        this->position = position;
    }

    Vec2 Circle::getPosition()
    {
        return this->position;
    }

    Vec2 Circle::getFarthestPointInDirection(Vec2 direction)
    {
        Vec2 farthestPoint = position + direction.norm() * radius;
        return farthestPoint;
    }

    void Circle::updateAABB(Vec2 offset, Angle angle)
    {
        aabb.update(offset + position - Vec2(radius), offset + position + Vec2(radius));
    }

    void Circle::updateArea()
    {
        area = M_PI * sq(radius);
    }

    Vec2 Circle::findCenterOfMass()
    {
        return position;
    }
}