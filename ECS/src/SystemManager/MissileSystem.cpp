/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** MissileSystem
*/

#include "../../include/SystemManager/MissileSystem.hpp"
#include "../../include/SystemManager/Entity.hpp"
#include "../../include/components/Health.hpp"
#include "../../include/components/Damages.hpp"
#include "../../include/components/Position.hpp"
#include "../../include/components/Speed.hpp"
#include "../../include/components/HitBox.hpp"

#include <algorithm> // For std::find_if

namespace Ecs {

    MissileSystem::MissileSystem(std::list<std::shared_ptr<Entity>> &entities)
        : ASystem(entities) {}

	std::shared_ptr<Entity> MissileSystem::createMissile(int entityID) noexcept {
        int id = 0;
        for (unsigned int i = 200; i < 500; i++)
        {
            if (!isIdTaken(i))
            {
                id = i;
                break;
            }
        }

        int speedToAdd = 0;
        int spawnPosX = 0;
        int spawnPosY = 0;

        if (entityID < 5) {
            spawnPosX = 25;
            speedToAdd = 20;
        }
        if (entityID >= 5 && entityID < 200) {
            spawnPosX = -40;
            speedToAdd = -15;
        }
        if (entityID == 600) {
            spawnPosX = -90;
            speedToAdd = -30;
        }

        auto missile = std::make_shared<Entity>(id);
        auto health = std::make_shared<Health>(1);
        auto damages = std::make_shared<Damages>(getEntityById(entityID)->getComponent<Ecs::Damages>()->getDamage());
        auto position = std::make_shared<Position>(getEntityById(entityID)->getComponent<Ecs::Position>()->getPosition().first + spawnPosX, getEntityById(entityID)->getComponent<Ecs::Position>()->getPosition().second + spawnPosY);
        auto hitbox = std::make_shared<Hitbox>(17, 18);
        auto speed = std::make_shared<Speed>(speedToAdd);
        missile->addComponent(health);
        missile->addComponent(damages);
        missile->addComponent(position);
        missile->addComponent(hitbox);
        missile->addComponent(speed);
        _Entities.push_back(missile);
        return missile;
    }

	void MissileSystem::updateMissiles() {
        //all entity with id between 100 and 200 move with their speed
        for (const auto &entity : _Entities)
        {
            if (entity->getEntityId() >= 200 && entity->getEntityId() < 500) {
                std::pair<int, int> pos = entity->getComponent<Ecs::Position>()->getPosition();
                entity->getComponent<Ecs::Position>()->set_pos_x(pos.first + entity->getComponent<Ecs::Speed>()->getSpeed());
            }
        }
	}

    bool MissileSystem::isIdTaken(unsigned int id) const noexcept {
        return std::any_of(_Entities.begin(), _Entities.end(), [id](const std::shared_ptr<Entity>& entity) {
            return entity->getEntityId() == id;
        });
    }

    std::shared_ptr<Entity> MissileSystem::getEntityById(unsigned int id)
    {
        for (auto &y : _Entities)
        {
            if (y.get()->getEntityId() == id)
                return y;
        }
        return nullptr;
    }

    void MissileSystem::launch() {
        updateMissiles();
    }

}
