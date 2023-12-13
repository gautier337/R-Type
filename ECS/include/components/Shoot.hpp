// Shoot.hpp
#ifndef SHOOT_HPP_
#define SHOOT_HPP_

#include "AComponent.hpp"
#include "../SystemManager/Entity.hpp"  // Include Entity class

namespace Ecs {
    class Shoot : public AComponent {
    public:
        Shoot();
        ~Shoot();
        void setSpeedShoot(int speed) noexcept { _speedShoot = speed; };
        int getSpeedShoot() noexcept { return _speedShoot; };
        void shoot();  // Function to shoot and create a missile entity

    private:
        int _speedShoot;
    };
} // namespace Ecs

#endif /* !SHOOT_HPP_ */