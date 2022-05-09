#include <include/NapiWrappers.hpp>

namespace addon
{
    String wrap(Env& env, std::string str)
    {
        return String::New(env, str);
    }

    Boolean wrap(Env& env, bool value)
    {
        return Boolean::New(env, value);
    }
    
    Number wrap(Env& env, rss::Angle angle)
    {
        return Number::New(env, angle.rad());
    }

    Number wrap(Env& env, double x)
    {
        return Number::New(env, x);
    }

    Object wrap(Env& env, rss::Vec2 vec)
    {
        Object obj = Object::New(env);

        obj.Set("x", wrap(env, vec.x));
        obj.Set("y", wrap(env, vec.y));

        return obj;
    }

    Object wrap(Env& env, rss::AABB aabb)
    {
        Object obj = Object::New(env);

        obj.Set("min", wrap(env, aabb.min));
        obj.Set("max", wrap(env, aabb.max));

        return obj;
    }

    Object wrap(Env& env, rss::Shape shape)
    {
        Object obj = Object::New(env);

        for (size_t i = 0; i < shape.parts.size(); i++)
            obj.Set(i, wrap(env, shape.parts[i]->aabb));
        
        return obj;
    }

    Object wrap(Env& env, rss::Object object)
    {
        Object obj = Object::New(env);

        obj.Set("name", wrap(env, object.name));

        obj.Set("position", wrap(env, object.position));
        obj.Set("velocity", wrap(env, object.velocity));

        obj.Set("mass",     wrap(env, object.mass));
        obj.Set("angle",    wrap(env, object.angle));
        obj.Set("w",        wrap(env, object.angularVelocity));
        obj.Set("inertia",  wrap(env, object.I));

        obj.Set("aabb",     wrap(env, object.aabb));
        obj.Set("COM",      wrap(env, object.centerOfMass));

        obj.Set("controllable", wrap(env, object.controllable));
        obj.Set("ghost",    wrap(env, object.ghost));

        obj.Set("shape",    wrap(env, object.shape));

        return obj;
    }

    Object wrap(Env& env, rss::World world)
    {
        Object allObjects = Object::New(env);

        for (int i = 0; i < world.objects.size(); i++)
            allObjects.Set(i, wrap(env, world.objects[i]));
        

        Object obj = Object::New(env);

        obj.Set("objects", allObjects);
        obj.Set("dt", wrap(env, world.dt));

        return obj;
    }
}