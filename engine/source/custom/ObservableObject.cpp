#include <include/custom/ObservableObject.hpp>

namespace soccer
{
    ObservableObject::ObservableObject()
    {
        avgVelocity = Vec2(0, 0);
        instantVelocity = Vec2(0, 0);
        position = Vec2(0, 0);
        ghost = false;
    }

    void ObservableObject::setup(Object object)
    {
        position = object.position;
    }

    void ObservableObject::update(Object object, double dt)
    {
        if (object.ghost)
        {
            ghost = true;
            return;
        }

        if (!object.ghost && ghost)
        {
            ghost = false;

            instantVelocity = Vec2(0, 0);
            avgVelocity = Vec2(0, 0);

            position = object.position;
        }
        
        instantVelocity = (object.position - position) / dt;

        if (avgVelocity.isZero())
            avgVelocity = instantVelocity;

        avgVelocity = avgVelocity * (1 - dt) + instantVelocity * dt;

        position = object.position;
    }
}