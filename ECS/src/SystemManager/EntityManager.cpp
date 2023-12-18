/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** EntityManager
*/

#include "../../include/SystemManager/EntityManager.hpp"
#include "../../include/components/Position.hpp"
#include "../../include/components/Health.hpp"
#include "../../include/components/Damages.hpp"
#include "../../include/components/Speed.hpp"


namespace Ecs {

    EntityManager::EntityManager() {}

    EntityManager::~EntityManager() {}

    unsigned int EntityManager::createPlayer() noexcept
    {
        int id = 0;
        for (unsigned int i = 1; i < 5; i++)
        {
            if (!isIdTaken(i))
            {
                id = i;
                break;
            }
        }
        auto player = std::make_shared<Entity>(id);
        auto health = std::make_shared<Health>(5);
        auto damages = std::make_shared<Damages>(3);
        auto position = std::make_shared<Position>(5, 5);
        player->addComponent(health);
        player->addComponent(damages);
        player->addComponent(position);
        _entityList.push_back(player);
        return player->getEntityId();
    }

    std::shared_ptr<Entity> EntityManager::createMonster(int entitySize, int hp, int dmg, int pos_x, int pos_y) noexcept
    {
        int id = 0;
        for (unsigned int i = 5; i < 201; i++)
        {
            if (!isIdTaken(i))
            {
                id = i;
                break;
            }
        }
        auto monster = std::make_shared<Entity>(id);
        auto health = std::make_shared<Health>(hp);
        auto damages = std::make_shared<Damages>(dmg);
        auto position = std::make_shared<Position>(pos_x, pos_y);
        monster->addComponent(health);
        monster->addComponent(damages);
        monster->addComponent(position);
        _entityList.push_back(monster);
        return monster;
    }

    std::shared_ptr<Entity> EntityManager::createMissile(int entityID) noexcept
    {
        int id = 0;
        for (unsigned int i = 201; i < 501; i++)
        {
            if (!isIdTaken(i))
            {
                id = i;
                break;
            }
        }

        int speedToAdd = 0;

        if (entityID < 5)
            speedToAdd = 3;
        if (entityID >= 5 && entityID < 101)
            speedToAdd = -3;

        auto missile = std::make_shared<Entity>(id);
        auto health = std::make_shared<Health>(1);
        auto damages = std::make_shared<Damages>(getEntityById(entityID)->getComponent<Ecs::Damages>()->getDamage());
        auto position = std::make_shared<Position>(getEntityById(entityID)->getComponent<Ecs::Position>()->getPosition().first, getEntityById(entityID)->getComponent<Ecs::Position>()->getPosition().second);
        auto speed = std::make_shared<Speed>(speedToAdd);
        missile->addComponent(health);
        missile->addComponent(damages);
        missile->addComponent(position);
        missile->addComponent(speed);
        _entityList.push_back(missile);
        return missile;
    }

    void EntityManager::updateMissiles()
    {
        //all entity with id between 100 and 200 move with their speed
        for (const auto &entity : _entityList)
        {
            if (entity->getEntityId() >= 201 && entity->getEntityId() <= 500) {
                std::pair<int, int> pos = entity->getComponent<Ecs::Position>()->getPosition();
                entity->getComponent<Ecs::Position>()->set_pox_x(pos.first + entity->getComponent<Ecs::Speed>()->getSpeed());
                entity->getComponent<Ecs::Position>()->set_pox_y(pos.second + entity->getComponent<Ecs::Speed>()->getSpeed());
            }
        }
    }

    void EntityManager::checkEntitiesState()
    {
        for (auto &entity : getEntsByComp<Ecs::Health>()) {
            if (entity->getComponent<Ecs::Health>()->getHp() <= 0) {
                deleteEntity(entity->getEntityId());
            }
        }
    }

    bool EntityManager::isIdTaken(unsigned int id) const noexcept
    {
        for (const auto &entity : _entityList)
        {
            if (entity->getEntityId() == id)
                return true;
        }
        return false;
    }

    unsigned int EntityManager::addEntity(Entity &entity) noexcept
    {
        _entityList.push_back(std::make_shared<Entity>(entity));
        return entity.getEntityId();
    }

    std::shared_ptr<Entity> EntityManager::getEntityById(unsigned int id)
    {
        for (auto &y : _entityList)
        {
            if (y.get()->getEntityId() == id)
                return y;
        }
        return nullptr;
    }

    bool EntityManager::deleteEntity(unsigned int id) noexcept
    {
        for (auto &y : _entityList)
        {
            if (y.get()->getEntityId() == id)
            {
                _entityList.remove(y);
                return true;
            }
        }
        return false;
    }

    int EntityManager::random(const int min, const int max) noexcept
    {
        return (rand() % (max - min + 1)) + min;
    }
}