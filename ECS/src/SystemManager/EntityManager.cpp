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
#include "../../include/components/ShootCD.hpp"
#include "../../include/components/Speed.hpp"
#include "../../include/components/HitBox.hpp"
#include "../../include/components/Constants.hpp"


namespace Ecs {

    EntityManager::EntityManager() : killedMonstersCount(0) {}

    EntityManager::~EntityManager() {}

    unsigned int EntityManager::createPlayer() noexcept
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
        _entityList.push_back(player);
        return player->getEntityId();
    }

    void EntityManager::handlePlayerInput(int id, int input) noexcept
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
            if (getEntityById(id)->getComponent<Ecs::Position>()->getPosition().second < 800)
                getEntityById(id)->getComponent<Ecs::Position>()->set_pox_y(getEntityById(id)->getComponent<Ecs::Position>()->getPosition().second + getEntityById(id)->getComponent<Ecs::Speed>()->getSpeed());
        }
        //Left
        if (input == 3) {
            if (getEntityById(id)->getComponent<Ecs::Position>()->getPosition().first > 0)
                getEntityById(id)->getComponent<Ecs::Position>()->set_pox_x(getEntityById(id)->getComponent<Ecs::Position>()->getPosition().first - getEntityById(id)->getComponent<Ecs::Speed>()->getSpeed());
        }
        //Right
        if (input == 4) {
            if (getEntityById(id)->getComponent<Ecs::Position>()->getPosition().first < 1000)
                getEntityById(id)->getComponent<Ecs::Position>()->set_pox_x(getEntityById(id)->getComponent<Ecs::Position>()->getPosition().first + getEntityById(id)->getComponent<Ecs::Speed>()->getSpeed());
        }
        //Shoot
        if (input == 5) {
            createMissile(id);
        }
    }

    std::shared_ptr<Entity> EntityManager::createMonster(int entitySize, int hp, int dmg, int pos_x, int pos_y, int speedM) noexcept
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
        auto hitbox = std::make_shared<Hitbox>(33, 34);
        auto speed = std::make_shared<Speed>(speedM);
        auto shootCooldown = std::make_shared<ShootCD>();
        monster->addComponent(health);
        monster->addComponent(damages);
        monster->addComponent(position);
        monster->addComponent(hitbox);
        monster->addComponent(speed);
        monster->addComponent(shootCooldown);
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
        int spawnPos = 0;

        if (entityID < 5) {
            spawnPos = 25;
            speedToAdd = 15;
        }
        if (entityID >= 5 && entityID < 101) {
            spawnPos = -40;
            speedToAdd = -15;
        }

        auto missile = std::make_shared<Entity>(id);
        auto health = std::make_shared<Health>(1);
        auto damages = std::make_shared<Damages>(getEntityById(entityID)->getComponent<Ecs::Damages>()->getDamage());
        auto position = std::make_shared<Position>(getEntityById(entityID)->getComponent<Ecs::Position>()->getPosition().first + spawnPos, getEntityById(entityID)->getComponent<Ecs::Position>()->getPosition().second);
        auto hitbox = std::make_shared<Hitbox>(17, 18);
        auto speed = std::make_shared<Speed>(speedToAdd);
        missile->addComponent(health);
        missile->addComponent(damages);
        missile->addComponent(position);
        missile->addComponent(hitbox);
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
            }
        }
    }

    void EntityManager::checkEntitiesState()
    {
        for (auto &entity : getEntsByComp<Ecs::Health>()) {
            if (entity->getComponent<Ecs::Health>()->getHp() <= 0) {
                if (entity->getEntityId() >= 5 && entity->getEntityId() <= 100)
                    increaseKilledMonstersCount();
                deleteEntity(entity->getEntityId());
            }
        }
        //check if missile is out of bounds
        for (auto &entity : getEntsByComp<Ecs::Position>()) {
            if (entity->getEntityId() >= 201 && entity->getEntityId() <= 500) {
                if (entity->getComponent<Ecs::Position>()->getPosition().first > 1080 || entity->getComponent<Ecs::Position>()->getPosition().first < 0)
                    deleteEntity(entity->getEntityId());
            }
        }
    }

    void EntityManager::generateMonsters()
    {
        static int frameCount = 0;
        const int framesPerMonster = 600; // 60 frames per second * 10 seconds

        // Generate a monster every 10 seconds
        if (frameCount % framesPerMonster == 0) {
            int xPos = random(780, 1080);
            int yPos = random(0, 1920);
            int entitySize = random(1, 3); // Assuming entitySize is the size of the monster
            int hp = random(1, 5);
            int dmg = random(1, 3);
            int speed = random(1, 3);

            createMonster(entitySize, hp, dmg, xPos, yPos, speed);
        }

        frameCount++;
    }

    void EntityManager::updateMonsters()
    {
        for (const auto& entity : _entityList)
        {
            if (entity->getEntityId() >= 5 && entity->getEntityId() <= 100)
            {
                auto position = entity->getComponent<Ecs::Position>();
                auto speed = entity->getComponent<Ecs::Speed>();

                // Update monster's position based on its speed
                std::pair<int, int> pos = position->getPosition();

                // Randomly choose a direction
                int direction = random(1, 4); // 1: top, 2: bottom, 3: left, 4: right

                // Move the monster accordingly
                if (direction == 1) {
                    position->set_pox_y(pos.second - speed->getSpeed()); // Move up
                } else if (direction == 2) {
                    position->set_pox_y(pos.second + speed->getSpeed()); // Move down
                } else if (direction == 3) {
                    position->set_pox_x(pos.first - speed->getSpeed()); // Move left
                } else {
                    position->set_pox_x(pos.first + speed->getSpeed()); // Move right
                }

                // Check and adjust X position to stay within bounds
                if (pos.first < 700)
                    position->set_pox_x(700);
                if (pos.first > 1080)
                    position->set_pox_x(1080);

                // Check and adjust Y position to stay within bounds
                if (pos.second < 0)
                    position->set_pox_y(0);
                if (pos.second > 1920)
                    position->set_pox_y(1920);

                // Shoot if the cooldown has expired
                for (const auto& entity : _entityList)
                {
                    if (entity->getEntityId() >= 5 && entity->getEntityId() <= 100)
                    {
                        auto shootCooldown = entity->getComponent<ShootCD>();

                        // Shoot if the cooldown has expired
                        if (shootCooldown->getCd() <= 0 && random(1, 5) == 1)
                        {
                            createMissile(entity->getEntityId());
                            shootCooldown->setCd(random(120, 300)); // 60 frames per second, so 2 to 5 seconds
                        }

                        shootCooldown->decreaseCd();
                    }
                }
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

    bool EntityManager::isGameOver() const
    {
        if (killedMonstersCount >= Constants::monstersToKillForWin)
            return true;
        return false;
    }

    void EntityManager::increaseKilledMonstersCount()
    {
        killedMonstersCount++;
    }
}