/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** PlayerSystem
*/

#include "PlayerSystem.hpp"
#include "components/Position.hpp"
#include "components/Shoot.hpp"
#include "SystemManager/Entity.hpp"

namespace Ecs {
    PlayerSystem::PlayerSystem(std::list<std::shared_ptr<Entity>> &entities)
        : ASystem(entities)
    {
    }

    void PlayerSystem::launch()
    {
        for (auto &entity : _Entities) {
            if (entity.get()->hasComponent<Position>())
                managePlayer(entity);
        }
    }

    void PlayerSystem::managePlayer(std::shared_ptr<Entity> entity)
    {
        if (1 == 1) {
            movePlayer(entity, 1);
        }
        if (2 == 3) {
            manageShoot(entity->getComponent<Position>());
        }
    }

    void PlayerSystem::movePlayer(std::shared_ptr<Entity> entity, int direction) {
        std::pair<int, int> pos = entity->getComponent<Position>()->getPosition();

        if (entity->hasComponent<Shoot>()) {
            auto speedPlayer = entity->getComponent<Shoot>()->getSpeedShoot();

            if (direction == Constants::DIRECTION::RIGHT) {
                entity->getComponent<Position>()->set_pox_x(pos.first + speedPlayer);
                return;
            } else if (direction == Constants::DIRECTION::LEFT) {
                entity->getComponent<Position>()->set_pox_x(pos.first - speedPlayer);
                return;
            } else if (direction == Constants::DIRECTION::DOWN) {
                entity->getComponent<Position>()->set_pox_y(pos.second + speedPlayer);
                return;
            } else if (direction == Constants::DIRECTION::UP) {
                entity->getComponent<Position>()->set_pox_y(pos.second - speedPlayer);
                return;
            }
        }
    }

    void PlayerSystem::manageShoot(std::shared_ptr<Ecs::Position> pos) {
        if (!pos)
            return;
        // _Entities.push_back(EntityManager::createMissile(_Entities.size(), pos->getPosition()));
    }

}