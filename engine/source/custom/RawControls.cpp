#include <include/custom/RawControls.hpp>

namespace soccer
{
    RawControls::RawControls(Vec2 velocity, double angularVelocity)
    {
        this->velocity = velocity;
        this->angularVelocity = angularVelocity;
    }
}