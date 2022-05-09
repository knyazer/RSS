#include <include/core/Rect.hpp>

namespace rss
{
    Rect::Rect()
    {
        min = Vec2(0, 0);
        max = Vec2(0, 0);
    }

    Rect::Rect(Vec2 min, Vec2 max)
    {
        this->min = min;
        this->max = max;

        setVertices(std::vector<Vec2>({min, Vec2(min.x, max.y), max, Vec2(max.x, min.y)}));
    }
}