#include <include/env/World.hpp>

namespace rss
{
    World::World()
    {
        objects.clear();
    }

    void World::step()
    {
        for (size_t i = 0; i < objects.size(); i++)
        {
            if (objects[i].fixed)
                continue;

            Vec2 friction =     objects[i].velocity.norm() * objects[i].friction * \
                                (objects[i].velocity.size() + 0.5);

            double angularFriction =    sign(objects[i].angularVelocity) * objects[i].angularFriction * \
                                        (abs(objects[i].angularVelocity) + 0.8);

            objects[i].acceleration -= friction;
            objects[i].angularAcceleration -= angularFriction;

            objects[i].angularVelocity += objects[i].angularAcceleration * dt;
            objects[i].angle += objects[i].angularVelocity * dt;

            objects[i].velocity += objects[i].acceleration * dt;
            objects[i].position += objects[i].velocity * dt;

            objects[i].updateAABB();
            objects[i].centerOfMass = objects[i].findCenterOfMass();

            objects[i].acceleration = 0;
            objects[i].angularAcceleration = 0;
        }
    }

    void World::resolve()
    {
        for (size_t i = 1; i < objects.size(); i++)
        {
            for (size_t j = 0; j < i; j++)
            {
                // Do not resolve collisions between fixed objects
                if (objects[i].fixed && objects[j].fixed)
                    continue;
                
                // Do not resolve collisions with ghost objects
                if (objects[i].ghost || objects[j].ghost)
                    continue;

                if (AABB::intersects(objects[i].shape.aabb, objects[j].shape.aabb))
                {
                    resolveForObjects(objects[i], objects[j]);
                }
            }
        }
    }

    Object& World::getObjectByName(std::string name)
    {
        for (size_t i = 0; i < objects.size(); i++)
            if (objects[i].name == name)
                return objects[i];

        std::cerr << "Fuck it, no name found, return first object" << std::endl;
        
        return objects[0];
    }

    void World::resolveForObjects(Object &A, Object &B)
    {
        for (size_t i = 0; i < A.shape.parts.size(); i++)
        {
            for (size_t j = 0; j < B.shape.parts.size(); j++)
            {
                if (AABB::intersects(A.shape.parts[i]->aabb, B.shape.parts[j]->aabb))
                {
                    resolveForConvexShapes(A, i, B, j);
                }
            }
        }
    }

    void World::resolveForConvexShapes(Object &A, size_t shapeA, Object &B, size_t shapeB)
    {
        ConvexShapeWrapper Aw = ConvexShapeWrapper(A.shape.parts[shapeA], A.angle, A.position);
        ConvexShapeWrapper Bw = ConvexShapeWrapper(B.shape.parts[shapeB], B.angle, B.position);

        Vec2 penetrationVector = Collision::getPenetrationVector(Aw, Bw);

        if (penetrationVector.isZero())
            return;
        
        if (penetrationVector.size() > 0.05)
            std::cout << "penetration vector " << penetrationVector << std::endl;

        Vec2 normal = penetrationVector.norm();

        Vec2 collisionPointA = Aw.getFarthestPointInDirection(penetrationVector);
        Vec2 collisionPointB = Bw.getFarthestPointInDirection(-penetrationVector);

        //std::cout << collisionPointA << " " << collisionPointB << std::endl;

        int AcollisionExists = int(Collision::exists(GJK::PointWrapper(collisionPointA), B));
        int BcollisionExists = int(Collision::exists(GJK::PointWrapper(collisionPointB), A));

        if (!AcollisionExists && !BcollisionExists)
        {
            std::cout << "Undetectable collision, though somehow detected. Most probably accuracy mistake" << std::endl;
            return;
        }

        Vec2 avgCollisionPoint =   (collisionPointA * AcollisionExists + collisionPointB * BcollisionExists) \
                                    / (AcollisionExists + BcollisionExists);

        Vec2 relativePointA = avgCollisionPoint - A.findCenterOfMass();
        Vec2 relativePointB = avgCollisionPoint - B.findCenterOfMass();

        Vec2 pointwiseVelocityA = A.velocity + relativePointA.star() * A.angularVelocity;
        Vec2 pointwiseVelocityB = B.velocity + relativePointB.star() * B.angularVelocity;

        Vec2 relativeCollisionVelocity = pointwiseVelocityA - pointwiseVelocityB;
        double collisionVelocity = relativeCollisionVelocity.dot(normal);

        if (collisionVelocity < 0)
            return;

        double invAmass = A.fixed ? 0 : (1 / A.mass);
        double invBmass = B.fixed ? 0 : (1 / B.mass);

        double invAI = A.fixed ? 0 : (1 / A.I);
        double invBI = B.fixed ? 0 : (1 / B.I);

        double impulseFactorA = (invAmass + sq(relativePointA.star().dot(normal)) * invAI);
        double impulseFactorB = (invBmass + sq(relativePointB.star().dot(normal)) * invBI);
        //std::cout << "impulse factors:" << impulseFactorA << " " << impulseFactorB << std::endl;

        double totalImpulseFactor = impulseFactorA + impulseFactorB;

        double restitution = max(A.restitution, B.restitution) * 0.6 + min(A.restitution, B.restitution) * 0.4;
        double impulseSize = collisionVelocity * (1 + restitution) / totalImpulseFactor;
        //std::cout << "collision velocity:" << collisionVelocity << std::endl;

        Vec2 impulse = -normal * impulseSize;
        //std::cout << "impulse:" << impulse << std::endl;

        //std::cout << "omegas1 " << A.angularVelocity << " " << B.angularVelocity << std::endl;
        A.angularVelocity = A.angularVelocity + relativePointA.star().dot(impulse) * invAI;
        B.angularVelocity = B.angularVelocity - relativePointB.star().dot(impulse) * invBI;
        //std::cout << "omegas2 " << A.angularVelocity << " " << B.angularVelocity << std::endl;

        A.velocity = A.velocity + impulse * invAmass;
        B.velocity = B.velocity - impulse * invBmass;
        //std::cout << "new velocities:" << A.velocity << " " << B.velocity << std::endl;

        double fixFactor = 0.1;
        if (!A.fixed && !B.fixed)
        {
            A.position = A.position - penetrationVector * B.mass / (A.mass + B.mass) * fixFactor;
            B.position = B.position + penetrationVector * A.mass / (A.mass + B.mass) * fixFactor;
        }
        else
        {
            if (!A.fixed)
                A.position = A.position - penetrationVector * fixFactor;
                
            if (!B.fixed)
                B.position = B.position + penetrationVector * fixFactor;
        }


        A.updateAABB();
        B.updateAABB();
    }
}