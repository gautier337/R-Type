/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** EntityManager
*/

#include "../include/EntityManager.hpp"
#include "../include/components/Position.hpp"

namespace Ecs {

    EntityManager::EntityManager() {}

    EntityManager::~EntityManager() {}

    unsigned int EntityManager::createPlayer() noexcept
    {
        auto entity = std::make_shared<Entity>(0);
        auto comp = std::make_shared<Position>(0, 0);
        _entityList.push_back(entity);
        return entity->getEntityId();
    }

    std::shared_ptr<Entity> EntityManager::createMonster(int entitySize) noexcept
    {
        auto entity = std::make_shared<Entity>(0);
        auto comp = std::make_shared<Position>(0, 0);
        entity->addComponent(comp);
        _entityList.push_back(entity);
        return entity;
    }

    std::shared_ptr<Entity> EntityManager::createMissile(int entitySize, std::pair<int, int> playerPos) noexcept
    {
        auto entity = std::make_shared<Entity>(0);
        auto comp = std::make_shared<Position>(playerPos.first + entitySize, playerPos.second + entitySize);
        entity->addComponent(comp);
        _entityList.push_back(entity);
        return entity;
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