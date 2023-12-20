#include "../../include/components/ShootCD.hpp"

namespace Ecs {

    ShootCD::ShootCD(int cd)
        : _cd(cd)
    { _type = Constants::SHOOTCD; }
    ShootCD::~ShootCD() {}

} // namespace Ecs