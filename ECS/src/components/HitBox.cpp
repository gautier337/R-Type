 #include "../../include/components/HitBox.hpp"

namespace Ecs {

    Hitbox::Hitbox(int height, int width)
        : _height(height), _width(width)
    { _type = Constants::HITBOX; }

    Hitbox::~Hitbox() {}
}