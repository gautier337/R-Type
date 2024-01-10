/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** EntitySystem
*/

#include "../../include/SystemManager/EntitySystem.hpp"
#include "../../include/components/Health.hpp"
#include "../../include/components/Position.hpp"

namespace Ecs {

    EntitySystem::EntitySystem(std::list<std::shared_ptr<Entity>> &entities)
        : ASystem(entities) {}


    void EntitySystem::checkEntitiesState() {
        //check basic monster
        for (auto &entity : getEntsByComp<Ecs::Health>()) {
            if (entity->getComponent<Ecs::Health>()->getHp() <= 0) {
                if (entity->getEntityId() >= 5 && entity->getEntityId() < 200) {
                    increaseKilledMonstersCount();
                    score += 10;
                }
                if (entity->getEntityId() >= 500 && entity->getEntityId() < 600) {
                    increaseKilledMonstersCount();
                    score += 20;
                }
                if (entity->getEntityId() == 600) {
                    increaseKilledMonstersCount();
                    score += 500;
                }
                deleteEntity(entity->getEntityId());
            }
        }
        //check if missile or kamikaze is out of bounds
        for (auto &entity : getEntsByComp<Ecs::Position>()) {
            if (entity->getEntityId() >= 200 && entity->getEntityId() < 500) {
                if (entity->getComponent<Ecs::Position>()->getPosition().first > 1930 || entity->getComponent<Ecs::Position>()->getPosition().first < -10)
                    deleteEntity(entity->getEntityId());
            }
            if (entity->getEntityId() >= 500 && entity->getEntityId() < 600) {
                if (entity->getComponent<Ecs::Position>()->getPosition().first < -40)
                    deleteEntity(entity->getEntityId());
            }
        }
    }

    void EntitySystem::increaseKilledMonstersCount() {
        killedMonstersCount++;
    }

    bool EntitySystem::deleteEntity(unsigned int id) noexcept {
        for (auto it = _Entities.begin(); it != _Entities.end(); ++it) {
            if ((*it)->getEntityId() == id) {
                _Entities.erase(it);
                return true;
            }
        }
        return false;
    }

    void EntitySystem::launch() {
        checkEntitiesState();
    }

}
