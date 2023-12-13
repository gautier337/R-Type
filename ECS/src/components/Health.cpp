#include "../../include/components/Health.hpp"

namespace Ecs {

    Health::Health(int hp)
        : _hp(hp)
    { _type = Constants::HEALTH; }
    Health::~Health() {}

} // namespace Ecs