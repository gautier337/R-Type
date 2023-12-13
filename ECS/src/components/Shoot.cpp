/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Shoot
*/

#include "../../include/components/Shoot.hpp"

namespace Ecs {

    Ecs::Shoot::Shoot()
        : _speedShoot(Constants::speedShoot)
    { _type = Constants::SPEEDSHOOT; }
    Shoot::~Shoot() {}

} // namespace Ecs
