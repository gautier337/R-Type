#include "../../include/components/Health.hpp"

namespace Ecs {

    Health::Health(int hp, int shield, int maxHp)
        : _hp(hp), _shield(shield), _maxHp(maxHp)
    { _type = Constants::HEALTH; }
    Health::~Health() {}

} // namespace Ecs