/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Shoot
*/

#ifndef SHOOT_HPP_
    #define SHOOT_HPP_
    #include "AComponent.hpp"

namespace Ecs {

    class Shoot : public AComponent {
        public:
            Shoot();
            ~Shoot();
            void setSpeedShoot(int speed) noexcept { _speedShoot = speed; };
            int getSpeedShoot() noexcept { return (_speedShoot); };
        private:
            int _speedShoot;
    };

}

#endif /* !SHOOT_HPP_ */
