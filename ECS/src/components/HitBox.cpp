 #include "../../include/components/HitBox.hpp"

namespace Ecs {

    Hitbox::Hitbox(int height, int width) noexcept
    {
        _height = height;
        _width = width;
    }

    Hitbox::~Hitbox() {}

    std::pair<int, int> Hitbox::getHitBoxSize()
    {
        return std::pair<int, int>(_height, _width);
    }
}