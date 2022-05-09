#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__

#include <include/core/Vec2.hpp>
#include <include/core/Angle.hpp>
#include <include/core/AABB.hpp>
#include <include/core/Shape.hpp>
#include <include/core/outputOverloads.hpp>
#include <string>
#include <cmath>

namespace rss
{
    class Object
    {
        public:
            std::string name;

            Vec2 position;
            Vec2 velocity;
            Vec2 acceleration;
            double friction;
            double mass;

            Angle angle;
            double angularVelocity;
            double angularAcceleration;
            double angularFriction;
            double I;

            double restitution;
            
            bool fixed;
            bool ghost;
            bool controllable;

            Shape shape;
            AABB aabb;

            Vec2 centerOfMass;

            Object(std::string name="");
            Object(Shape shape, Vec2 position, std::string name="");
            void setDefaultValues();
            void finalize();

            void setPosition(Vec2 position);
            void fix();

            Vec2 getFarthestPointInDirection(Vec2 direction);

            void updateAABB(bool force=false);

            Object(const Object&) = default;

            Vec2 findCenterOfMass();
        
        private:
            std::string generateRandomName();
    };
}

#endif