#include "../../include/components/Speed.hpp"

namespace Ecs {
    Speed::Speed(int speed)
        : _speed(speed)
        { _type = Constants::SPEED; }
    Speed::~Speed() {};
}