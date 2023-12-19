 #include "../../include/components/HitBox.hpp"

namespace Ecs {

    Hitbox::Hitbox(int height, int width) noexcept
    {
        _height = height;
        _width = width;
    }

    Hitbox::~Hitbox() {}
}