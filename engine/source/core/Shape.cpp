#include <include/core/Shape.hpp>

namespace rss
{
    Shape::Shape()
    {
    }

    Vec2 Shape::getFarthestPointInDirection(Vec2 direction)
    {
        if (parts.size() == 0)
            throw std::runtime_error("Shape size is zero, probably you forgot to init the Shape object");
        
        Vec2 farthestPoint = parts[0]->getFarthestPointInDirection(direction);

        for (int i = 1; i < parts.size(); i++)
        {
            Vec2 FarthestPointOfShapePart = parts[i]->getFarthestPointInDirection(direction);

            if (farthestPoint.dot(direction) < FarthestPointOfShapePart.dot(direction))
                farthestPoint = FarthestPointOfShapePart;
        }

        return farthestPoint;
    }

    void Shape::updateAABB(Vec2 position, Angle angle)
    {
        for (int i = 0; i < parts.size(); i++)
            parts[i]->updateAABB(position, angle);

        aabb = parts[0]->aabb;

        for (int i = 1; i < parts.size(); i++)
            aabb = AABB::merge(aabb, parts[i]->aabb);
    }

    Vec2 Shape::findCenterOfMass()
    {
        Vec2 centerOfMass = Vec2(0, 0);
        double totalArea = 0;
        for (int i = 0; i < parts.size(); i++)
        {
            parts[i]->updateArea();
            centerOfMass += (parts[i]->findCenterOfMass()) * (parts[i]->area);
            totalArea += parts[i]->area;
        }

        return centerOfMass / totalArea;
    }

    void Shape::finalize()
    {
        centerOfMass = findCenterOfMass();
    }
}