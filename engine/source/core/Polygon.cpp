#include <include/core/Polygon.hpp>

namespace rss
{
    Polygon::Polygon()
    {

    }

    Polygon::Polygon(std::vector<Vec2> vertices)
    {
        setVertices(vertices);
    }

    void Polygon::setVertices(std::vector<Vec2> v)
    {
        vertices = v;
        if (isWindingLeft())
            std::reverse(vertices.begin(), vertices.end());
    }

    void Polygon::updateArea()
    {
        area = abs(getSignedArea());
    }

    double Polygon::getSignedArea()
    {
        double res = 0;
        for (size_t i = 0; i < vertices.size(); i++)
        {
            int j = i + 1;
            if (j == vertices.size())
                j = 0;
            
            res += (vertices[j].x - vertices[i].x) * (vertices[j].y + vertices[i].y);
        }

        return res;
    }

    bool Polygon::isWindingLeft()
    {
        return getSignedArea() > 0;
    }

    Vec2 Polygon::findCenterOfMass()
    {
        Vec2 centerOfMass = Vec2(0, 0);
        for (size_t i = 0; i < vertices.size(); i++)
            centerOfMass += vertices[i];
        return centerOfMass / vertices.size();
    }

    Vec2 Polygon::getFarthestPointInDirection(Vec2 direction)
    {
        double bestVertexProj = vertices[0].dot(direction);
        int bestVertexI = 0;

        for (int i = 1, size = vertices.size(); i < size; i++)
        {
            double proj = vertices[i].dot(direction);
            if (proj > bestVertexProj)
            {
                bestVertexProj = proj;
                bestVertexI = i;
            }
        }

        return vertices[bestVertexI];
    }
}