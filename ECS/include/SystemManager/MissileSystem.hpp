/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** MissileSystem
*/

#ifndef MISSILESYSTEM_HPP_
#define MISSILESYSTEM_HPP_

#include "ASystem.hpp"
#include <list>
#include <memory>
#include "Entity.hpp"

namespace Ecs {

    class MissileSystem : public ASystem {
    public:
        MissileSystem(std::list<std::shared_ptr<Entity>> &entities);

        std::shared_ptr<Entity> createMissile(int entityID) noexcept;
        void updateMissiles();
		bool isIdTaken(unsigned int id) const noexcept;
        std::shared_ptr<Entity> getEntityById(unsigned int id);
        void launch() final;
    };

}

#endif /* MISSILESYSTEM_HPP_ */
