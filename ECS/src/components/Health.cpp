#include "../../include/components/Health.hpp"

namespace Ecs {

    Health::Health(int hp, int shield)
        : _hp(hp), _shield(shield)
    { _type = Constants::HEALTH; }
    Health::~Health() {}

} // namespace Ecs