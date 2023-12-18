#include "../../include/components/Damages.hpp"

namespace Ecs {

    Damages::Damages(int dmg)
        : _damage(dmg)
    { _type = Constants::DAMAGES; }
    Damages::~Damages() {}

} // namespace Ecs