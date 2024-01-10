/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** PlayerSystem
*/

#include "../../include/SystemManager/PlayerSystem.hpp"
#include "../../include/SystemManager/Entity.hpp"
#include "../../include/components/Position.hpp"
#include "../../include/components/Speed.hpp"

namespace Ecs {
    PlayerSystem::PlayerSystem(std::list<std::shared_ptr<Entity>> &entities)
        : ASystem(entities)
    {
    }

    PlayerSystem::~PlayerSystem()
    {
    }

    unsigned int PlayerSystem::createPlayer() noexcept
    {
        int id = 0;
        std::pair<int, int> pos;

        for (unsigned int i = 1; i < 5; i++)
        {
            if (!isIdTaken(i))
            {
                id = i;
                break;
            }
        }

        if (id == 0)
            return 0;
        if (id == 1)
            pos = std::make_pair(200, 340);
        if (id == 2)
            pos = std::make_pair(200, 440);
        if (id == 3)
            pos = std::make_pair(200, 640);
        if (id == 4)
            pos = std::make_pair(200, 740);
        auto player = std::make_shared<Entity>(id);
        auto health = std::make_shared<Health>(5);
        auto damages = std::make_shared<Damages>(3);
        auto position = std::make_shared<Position>(pos.first, pos.second);
        auto hitbox = std::make_shared<Hitbox>(17, 18);
        auto speed = std::make_shared<Speed>(10);
        player->addComponent(health);
        player->addComponent(damages);
        player->addComponent(position);
        player->addComponent(hitbox);
        player->addComponent(speed);
        _Entities.push_back(player);
        return player->getEntityId();
    }

    void PlayerSystem::handlePlayerInput(int id, int input) noexcept
    {
        //check if entity exist
        if (!isIdTaken(id))
            return;
        //Down
        if (input == 1) {
            if (getEntityById(id)->getComponent<Ecs::Position>()->getPosition().second > 0)
                getEntityById(id)->getComponent<Ecs::Position>()->set_pox_y(getEntityById(id)->getComponent<Ecs::Position>()->getPosition().second - getEntityById(id)->getComponent<Ecs::Speed>()->getSpeed());
        }
        //Up
        if (input == 2) {
            if (getEntityById(id)->getComponent<Ecs::Position>()->getPosition().second < 1080)
                getEntityById(id)->getComponent<Ecs::Position>()->set_pox_y(getEntityById(id)->getComponent<Ecs::Position>()->getPosition().second + getEntityById(id)->getComponent<Ecs::Speed>()->getSpeed());
        }
        //Left
        if (input == 3) {
            if (getEntityById(id)->getComponent<Ecs::Position>()->getPosition().first > 0)
                getEntityById(id)->getComponent<Ecs::Position>()->set_pox_x(getEntityById(id)->getComponent<Ecs::Position>()->getPosition().first - getEntityById(id)->getComponent<Ecs::Speed>()->getSpeed());
        }
        //Right
        if (input == 4) {
            if (getEntityById(id)->getComponent<Ecs::Position>()->getPosition().first < 500)
                getEntityById(id)->getComponent<Ecs::Position>()->set_pox_x(getEntityById(id)->getComponent<Ecs::Position>()->getPosition().first + getEntityById(id)->getComponent<Ecs::Speed>()->getSpeed());
        }
        //Shoot
        if (input == 5) {
            createMissile(id);
        }
    }

    std::shared_ptr<Entity> PlayerSystem::createMissile(int entityID) noexcept
    {
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

    bool PlayerSystem::isIdTaken(unsigned int id) const noexcept {
        return std::any_of(_Entities.begin(), _Entities.end(), [id](const std::shared_ptr<Entity>& entity) {
            return entity->getEntityId() == id;
        });
    }

	std::shared_ptr<Entity> PlayerSystem::getEntityById(unsigned int id)
    {
        for (auto &y : _Entities)
        {
            if (y.get()->getEntityId() == id)
                return y;
        }
        return nullptr;
    }

    void PlayerSystem::launch() {
        return;
    }

}