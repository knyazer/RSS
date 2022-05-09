#include <include/core/Object.hpp>

namespace rss
{
    Object::Object(std::string name)
    {
        setDefaultValues();

        if (name == "")
            this->name = generateRandomName();
        else
            this->name = name;
    }

    Object::Object(Shape shape, Vec2 position, std::string name)
    {
        setDefaultValues();

        this->shape = shape;
        this->position = position;

        if (name == "")
            this->name = generateRandomName();
        else
            this->name = name;

        updateAABB();
    }

    void Object::setDefaultValues()
    {
        position = Vec2(0, 0);
        velocity = Vec2(0, 0);
        acceleration = Vec2(0, 0);
        friction = 0.5;
        mass = 1;

        angle = 0;
        angularVelocity = 0;
        angularAcceleration = 0;
        angularFriction = 0.5;
        I = 1;
        controllable = false;

        restitution = 0.5;
        fixed = false;
        ghost = false;
    }

    void Object::finalize()
    {
        updateAABB(true);
        shape.finalize();

        if (!fixed)
        {
            double r = (aabb.max - aabb.min).size() / 2;
            I = mass / 100;
        }
    }

    void Object::setPosition(Vec2 position)
    {
        this->position = position;
    }

    Vec2 Object::getFarthestPointInDirection(Vec2 direction)
    {
        return position + shape.getFarthestPointInDirection(direction.rotate(-angle)).rotate(angle); // SAME 1
    }

    void Object::updateAABB(bool force)
    {
        if (!fixed || force)
        {
            shape.updateAABB(position, angle);
            aabb.update(shape.aabb.min, shape.aabb.max);
        }
    }

    void Object::fix()
    {
        fixed = true;

        I = 0;
        mass = 0;

        updateAABB(true);
    }

    Vec2 Object::findCenterOfMass()
    {
        return position + shape.centerOfMass.rotate(angle);
    }

    std::string Object::generateRandomName()
    {
        std::string res = "";
        for (size_t i = 0; i < 12; i++)
            res += char('A' + char(randf() * 26));

        return res;
    }
}