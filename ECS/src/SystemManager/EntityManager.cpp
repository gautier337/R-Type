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
#include <cmath>


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
        auto shootCooldown = std::make_shared<ShootCD>(1);
        player->addComponent(health);
        player->addComponent(damages);
        player->addComponent(position);
        player->addComponent(hitbox);
        player->addComponent(speed);
        player->addComponent(shootCooldown);
        player->getComponent<ShootCD>()->setMultiShoot(false);
        _entityList.push_back(player);
        return player->getEntityId();
    }

    void EntityManager::updatePlayers()
    {
        static int frameCount = 0;
        const int framesForShootCD = 30; // 0.5 seconds
        const int framesForRegen = 600; // 10 second
        static int frameCountMultiShoot = 0;

        for (const auto &entity : _entityList)
        {
            if (entity->getEntityId() >= 1 && entity->getEntityId() < 5)
            {
                if (frameCount % framesForShootCD == 0) {
                    if (entity->getComponent<ShootCD>()->getCd() > 0) {
                        entity->getComponent<ShootCD>()->setCd(entity->getComponent<ShootCD>()->getCd() - 0.1);
                        if (entity->getComponent<ShootCD>()->getMultiShoot() == true) {
                            entity->getComponent<ShootCD>()->setCd(entity->getComponent<ShootCD>()->getCd() - 0.1);
                        }
                    }
                }
                if (frameCount % framesForRegen == 0) {
                    if (entity->getComponent<Health>()->getHp() < 5)
                        entity->getComponent<Health>()->setHp(entity->getComponent<Health>()->getHp() + 1);
                }
                if (entity->getComponent<ShootCD>()->getMultiShoot() == true) {
                    if (frameCountMultiShoot >= 300) {
                        entity->getComponent<ShootCD>()->setMultiShoot(false);
                        frameCountMultiShoot = 0;
                    }
                    frameCountMultiShoot++;
                }
                // if player shield is not 0, decrease it by 1 every 0.5 seconds
                if (entity->getComponent<Health>()->getShield() > 0) {
                    if (frameCount % framesForShootCD == 0) {
                        entity->getComponent<Health>()->setShield(entity->getComponent<Health>()->getShield() - 1);
                    }
                    updateShields(entity);
                }
            }
        }
        frameCount++;
    }

    void EntityManager::updateShields(std::shared_ptr<Entity> entity)
    {

        // if no shield entity, create one
        if (entity->getEntityId() == 1 && getEntityById(801) == nullptr) {
            auto shield = std::make_shared<Entity>(801);
            auto health = std::make_shared<Health>(entity->getComponent<Ecs::Health>()->getShield());
            auto position = std::make_shared<Position>(entity->getComponent<Ecs::Position>()->getPosition().first + 30, entity->getComponent<Ecs::Position>()->getPosition().second);
            auto hitbox = std::make_shared<Hitbox>(17, 18);
            auto damages = std::make_shared<Damages>(1);
            shield->addComponent(health);
            shield->addComponent(position);
            shield->addComponent(hitbox);
            shield->addComponent(damages);
            _entityList.push_back(shield);
        } else if (entity->getEntityId() == 1 && getEntityById(801) != nullptr) {
            getEntityById(801)->getComponent<Ecs::Health>()->setHp(entity->getComponent<Ecs::Health>()->getShield());
            getEntityById(801)->getComponent<Ecs::Position>()->set_pos_x(entity->getComponent<Ecs::Position>()->getPosition().first + 30);
            getEntityById(801)->getComponent<Ecs::Position>()->set_pos_y(entity->getComponent<Ecs::Position>()->getPosition().second);
        }
        if (entity->getEntityId() == 2 && getEntityById(802) == nullptr) {
            auto shield = std::make_shared<Entity>(802);
            auto health = std::make_shared<Health>(entity->getComponent<Ecs::Health>()->getShield());
            auto position = std::make_shared<Position>(entity->getComponent<Ecs::Position>()->getPosition().first + 30, entity->getComponent<Ecs::Position>()->getPosition().second);
            auto hitbox = std::make_shared<Hitbox>(17, 18);
            auto damages = std::make_shared<Damages>(1);
            shield->addComponent(health);
            shield->addComponent(position);
            shield->addComponent(hitbox);
            shield->addComponent(damages);
            _entityList.push_back(shield);
        } else if (entity->getEntityId() == 2 && getEntityById(802) != nullptr) {
            getEntityById(802)->getComponent<Ecs::Health>()->setHp(entity->getComponent<Ecs::Health>()->getShield());
            getEntityById(802)->getComponent<Ecs::Position>()->set_pos_x(entity->getComponent<Ecs::Position>()->getPosition().first + 30);
            getEntityById(802)->getComponent<Ecs::Position>()->set_pos_y(entity->getComponent<Ecs::Position>()->getPosition().second);
        }
        if (entity->getEntityId() == 3 && getEntityById(803) == nullptr) {
            auto shield = std::make_shared<Entity>(803);
            auto health = std::make_shared<Health>(entity->getComponent<Ecs::Health>()->getShield());
            auto position = std::make_shared<Position>(entity->getComponent<Ecs::Position>()->getPosition().first + 30, entity->getComponent<Ecs::Position>()->getPosition().second);
            auto hitbox = std::make_shared<Hitbox>(17, 18);
            auto damages = std::make_shared<Damages>(1);
            shield->addComponent(health);
            shield->addComponent(position);
            shield->addComponent(hitbox);
            shield->addComponent(damages);
            _entityList.push_back(shield);
        } else if (entity->getEntityId() == 3 && getEntityById(803) != nullptr) {
            getEntityById(803)->getComponent<Ecs::Health>()->setHp(entity->getComponent<Ecs::Health>()->getShield());
            getEntityById(803)->getComponent<Ecs::Position>()->set_pos_x(entity->getComponent<Ecs::Position>()->getPosition().first + 30);
            getEntityById(803)->getComponent<Ecs::Position>()->set_pos_y(entity->getComponent<Ecs::Position>()->getPosition().second);
        }
        if (entity->getEntityId() == 4 && getEntityById(804) == nullptr) {
            auto shield = std::make_shared<Entity>(804);
            auto health = std::make_shared<Health>(entity->getComponent<Ecs::Health>()->getShield());
            auto position = std::make_shared<Position>(entity->getComponent<Ecs::Position>()->getPosition().first + 30, entity->getComponent<Ecs::Position>()->getPosition().second);
            auto hitbox = std::make_shared<Hitbox>(17, 18);
            auto damages = std::make_shared<Damages>(1);
            shield->addComponent(health);
            shield->addComponent(position);
            shield->addComponent(hitbox);
            shield->addComponent(damages);
            _entityList.push_back(shield);
        } else if (entity->getEntityId() == 4 && getEntityById(804) != nullptr) {
            getEntityById(804)->getComponent<Ecs::Health>()->setHp(entity->getComponent<Ecs::Health>()->getShield());
            getEntityById(804)->getComponent<Ecs::Position>()->set_pos_x(entity->getComponent<Ecs::Position>()->getPosition().first + 30);
            getEntityById(804)->getComponent<Ecs::Position>()->set_pos_y(entity->getComponent<Ecs::Position>()->getPosition().second);
        }
    }

    void EntityManager::handlePlayerInput(int id, int input) noexcept
    {
        //check if entity exist
        if (!isIdTaken(id))
            return;
        //Down
        if (input == 1) {
            if (getEntityById(id)->getComponent<Ecs::Position>()->getPosition().second > 0)
                getEntityById(id)->getComponent<Ecs::Position>()->set_pos_y(getEntityById(id)->getComponent<Ecs::Position>()->getPosition().second - getEntityById(id)->getComponent<Ecs::Speed>()->getSpeed());
        }
        //Up
        if (input == 2) {
            if (getEntityById(id)->getComponent<Ecs::Position>()->getPosition().second < 1080)
                getEntityById(id)->getComponent<Ecs::Position>()->set_pos_y(getEntityById(id)->getComponent<Ecs::Position>()->getPosition().second + getEntityById(id)->getComponent<Ecs::Speed>()->getSpeed());
        }
        //Left
        if (input == 3) {
            if (getEntityById(id)->getComponent<Ecs::Position>()->getPosition().first > 0)
                getEntityById(id)->getComponent<Ecs::Position>()->set_pos_x(getEntityById(id)->getComponent<Ecs::Position>()->getPosition().first - getEntityById(id)->getComponent<Ecs::Speed>()->getSpeed());
        }
        //Right
        if (input == 4) {
            if (getEntityById(id)->getComponent<Ecs::Position>()->getPosition().first < 500)
                getEntityById(id)->getComponent<Ecs::Position>()->set_pos_x(getEntityById(id)->getComponent<Ecs::Position>()->getPosition().first + getEntityById(id)->getComponent<Ecs::Speed>()->getSpeed());
        }
        //Shoot
        if (input == 5) {
            if (getEntityById(id)->getComponent<ShootCD>()->getCd() <= 0) {
                if (getEntityById(id)->getComponent<ShootCD>()->getMultiShoot() == true) {
                    createMissile(id);
                    createMissile(id, 40);
                    createMissile(id, -40);
                } else {
                    createMissile(id);
                }
                getEntityById(id)->getComponent<ShootCD>()->setCd(1);
            }
        }
    }

    std::shared_ptr<Entity> EntityManager::createMonster(int hp, int dmg, int pos_x, int pos_y, int speedM, int id_min, int id_max, int hitboxX, int hitboxY) noexcept
    {
        int id = 0;
        for (unsigned int i = id_min; i < id_max; i++)
        {
            if (!isIdTaken(i))
            {
                id = i;
                break;
            }
        }
        if (id == 0)
            return nullptr;
        auto monster = std::make_shared<Entity>(id);
        auto health = std::make_shared<Health>(hp);
        auto damages = std::make_shared<Damages>(dmg);
        auto position = std::make_shared<Position>(pos_x, pos_y);
        auto hitbox = std::make_shared<Hitbox>(hitboxX, hitboxY);
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

    std::shared_ptr<Entity> EntityManager::createMissile(int entityID, int posY) noexcept
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
            spawnPosX = 35;
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

        auto missile = std::make_shared<Entity>(id, entityID);
        auto health = std::make_shared<Health>(1);
        auto damages = std::make_shared<Damages>(getEntityById(entityID)->getComponent<Ecs::Damages>()->getDamage());
        auto position = std::make_shared<Position>(getEntityById(entityID)->getComponent<Ecs::Position>()->getPosition().first + spawnPosX, getEntityById(entityID)->getComponent<Ecs::Position>()->getPosition().second + spawnPosY + posY);
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
            if (entity->getEntityId() >= 200 && entity->getEntityId() < 500) {
                std::pair<int, int> pos = entity->getComponent<Ecs::Position>()->getPosition();
                entity->getComponent<Ecs::Position>()->set_pos_x(pos.first + entity->getComponent<Ecs::Speed>()->getSpeed());
            }
        }
    }

    void EntityManager::checkEntitiesState()
    {
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
        //check if missile or kamikaze or boosts is out of bounds
        for (auto &entity : getEntsByComp<Ecs::Position>()) {
            if (entity->getEntityId() >= 200 && entity->getEntityId() < 500) {
                if (entity->getComponent<Ecs::Position>()->getPosition().first > 1930 || entity->getComponent<Ecs::Position>()->getPosition().first < -10)
                    deleteEntity(entity->getEntityId());
            }
            if (entity->getEntityId() >= 500 && entity->getEntityId() < 600) {
                if (entity->getComponent<Ecs::Position>()->getPosition().first < -40)
                    deleteEntity(entity->getEntityId());
            }
            if (entity->getEntityId() >= 700 && entity->getEntityId() < 730) {
                if (entity->getComponent<Ecs::Position>()->getPosition().second > 1120)
                    deleteEntity(entity->getEntityId());
            }
        }

    }

    void EntityManager::generateBoss1()
    {
        createMonster(50, 5, 1200, 540, 2, 600, 601, 160, 210);
    }

    void EntityManager::generateBasicMonster()
    {
        int xPos = random(1300, 1500);
        int yPos = random(100, 980);
        createMonster(3, 1, xPos, yPos, 2, 5, 200, 33, 34);
    }

    void EntityManager::generateAsteroid()
    {
        int xPos = 1950;
        int yPos = random(0, 1080);
        int randomSpeed = random(10, 13);
        if (randomSpeed == 11) {
            xPos = random(0, 1920);
            yPos = 1120;
        } else if (randomSpeed == 12) {
            xPos = random(0, 1920);
            yPos = -40;
        }
        createMonster(9, 1, xPos, yPos, randomSpeed, 601, 650, 60, 63);
    }

    void EntityManager::generateKamikaze()
    {
        int xPos = random(1100, 1300);
        int yPos = random(100, 980);
        createMonster(1, 10, xPos, yPos, 8, 500, 600, 33, 32);
    }

    void EntityManager::generateHealthBoost()
    {
        int xPos = random(100, 1000);
        int yPos = -100;
        createMonster(1, 1, xPos, yPos, 2, 700, 710, 15, 15);
    }

    void EntityManager::generateShootBoost()
    {
        int xPos = random(100, 1000);
        int yPos = -100;
        createMonster(1, 1, xPos, yPos, 2, 710, 720, 15, 15);
    }

    void EntityManager::generateShieldBoost()
    {
        int xPos = random(100, 1000);
        int yPos = -100;
        createMonster(1, 1, xPos, yPos, 2, 720, 730, 15, 15);
    }

    void EntityManager::generateMonsters()
    {
        static int frameCount = 0;
        const int framesPerMonster = 180; // 60 frames per second * 3 seconds

        // Generate a monster every 3 seconds
        if (frameCount % framesPerMonster == 0) {

            // Generate a random number between 0 and 9
            int randomNum = random(0, 10);

            if (wave == 1) {
                if (randomNum < 8) {
                    generateBasicMonster();
                }
                if (randomNum < 4) {
                    generateAsteroid();
                }
                if (randomNum < 2) {
                    generateHealthBoost();
                }
                if (randomNum > 8) {
                    generateShootBoost();
                }
            } else if (wave == 2) {
                if (randomNum < 8) {
                    generateBasicMonster();
                } else {
                    generateKamikaze();
                }
                if (randomNum < 4) {
                    generateAsteroid();
                }
                if (randomNum < 2) {
                    generateHealthBoost();
                }
                if (randomNum > 8) {
                    generateShootBoost();
                }
            } else if (wave == 3) {
                generateBoss1();
                if (randomNum < 2) {
                    generateHealthBoost();
                }
                if (randomNum > 8) {
                    generateShootBoost();
                }
            } else {
                if (randomNum < 6) {
                    generateBasicMonster();
                }
                if (randomNum > 8) {
                    generateKamikaze();
                }
                if (randomNum < 4) {
                    generateAsteroid();
                }
                if (randomNum < 2) {
                    generateHealthBoost();
                }
                if (randomNum > 8) {
                    generateShootBoost();
                }
                if (randomNum == 5) {
                    generateShieldBoost();
                }
            }
        }
        frameCount++;
    }


    void EntityManager::updateMonsters()
    {
        for (const auto& entity : _entityList)
        {
            //Basic
            if (entity->getEntityId() >= 5 && entity->getEntityId() < 200)
            {
                auto position = entity->getComponent<Ecs::Position>();
                auto speed = entity->getComponent<Ecs::Speed>();

                // Update monster's position based on its speed
                std::pair<int, int> pos = position->getPosition();

                // Randomly choose a direction
                int direction = random(1, 4); // 1: top, 2: bottom, 3: left, 4: right

                // Move the monster accordingly
                if (direction == 1) {
                    position->set_pos_y(pos.second - speed->getSpeed()); // Move up
                } else if (direction == 2) {
                    position->set_pos_y(pos.second + speed->getSpeed()); // Move down
                } else if (direction == 3) {
                    position->set_pos_x(pos.first - speed->getSpeed()); // Move left
                } else {
                    position->set_pos_x(pos.first + speed->getSpeed()); // Move right
                }

                // Check and adjust Y position to stay within bounds
                if (pos.second < 0)
                    position->set_pos_y(0);
                if (pos.second > 1920)
                    position->set_pos_y(1920);

                // Shoot if the cooldown has expired
                for (const auto& entity : _entityList)
                {
                    if (entity->getEntityId() >= 5 && entity->getEntityId() < 200)
                    {
                        auto shootCooldown = entity->getComponent<ShootCD>();

                        // Shoot if the cooldown has expired
                        if (shootCooldown->getCd() <= 0 && random(1, 5) == 1)
                        {
                            createMissile(entity->getEntityId());
                            shootCooldown->setCd(random(300, 480)); // 60 frames per second, so 5 to 8 seconds
                        }

                        shootCooldown->decreaseCd();
                    }
                }
            }
            // Kamikaze
            if (entity->getEntityId() >= 500 && entity->getEntityId() < 600)
            {
                auto position = entity->getComponent<Ecs::Position>();
                auto speed = entity->getComponent<Ecs::Speed>();

                // Update monster's position based on its speed
                std::pair<int, int> pos = position->getPosition();

                // Find the player's position (if any player entity is present)
                std::shared_ptr<Entity> player = nullptr;
                for (int playerId = 1; playerId <= 4; ++playerId)
                {
                    player = getEntityById(playerId);
                    if (player != nullptr)
                        break;
                }

                // If no player entity is found, move kamikaze monster straight ahead
                if (player == nullptr)
                {
                    position->set_pos_x(pos.first + speed->getSpeed());
                    position->set_pos_y(pos.second);
                }
                else
                {
                    // Calculate direction towards the player
                    int deltaY = player->getComponent<Ecs::Position>()->getPosition().second - pos.second;
                    int m = 0;

                    if (deltaY > 0)
                        m = 1;
                    else
                        m = -1;

                    // Move the kamikaze monster towards the player
                    position->set_pos_x(pos.first - speed->getSpeed());
                    if (deltaY != 0)
                        position->set_pos_y(pos.second + (speed->getSpeed() * m));
                }

                // Check and adjust Y position to stay within bounds
                if (pos.second < 0)
                    position->set_pos_y(0);
                if (pos.second > 1920)
                    position->set_pos_y(1920);
            }
            // Boss (ID 600)
            if (entity->getEntityId() == 600)
            {
                auto position = entity->getComponent<Ecs::Position>();
                auto speed = entity->getComponent<Ecs::Speed>();
                auto shootCooldown = entity->getComponent<ShootCD>();

                // Update boss's position based on its speed
                std::pair<int, int> pos = position->getPosition();

                // Find the player's position (if any player entity is present)
                std::shared_ptr<Entity> player = nullptr;
                for (int playerId = 1; playerId <= 4; ++playerId)
                {
                    player = getEntityById(playerId);
                    if (player != nullptr)
                        break;
                }

                // If no player entity is found, move boss straight ahead
                if (player == nullptr)
                {
                    position->set_pos_x(pos.first - speed->getSpeed());
                    position->set_pos_y(pos.second);
                }
                else
                {
                    // Calculate direction towards the player
                    int deltaY = player->getComponent<Ecs::Position>()->getPosition().second - pos.second;
                    int m = 0;

                    if (deltaY > 0)
                        m = 1;
                    else
                        m = -1;

                    // Move the boss towards the player
                    if (deltaY != 0)
                        position->set_pos_y(pos.second + (speed->getSpeed() * m));
                }

                // Check and adjust Y position to stay within bounds
                if (pos.second < 0)
                    position->set_pos_y(0);
                if (pos.second > 1920)
                    position->set_pos_y(1920);

                // Shoot more frequently compared to regular monsters
                if (shootCooldown->getCd() <= 0 && random(1, 3) == 1)
                {
                    createMissile(entity->getEntityId());
                    shootCooldown->setCd(random(180, 300)); // 60 frames per second, so 3 to 5 seconds
                }

                shootCooldown->decreaseCd();
            }
            //Asteroid (ID 601 to 650)
            if (entity->getEntityId() >= 601 && entity->getEntityId() < 650)
            {
                auto position = entity->getComponent<Ecs::Position>();
                int speed = entity->getComponent<Ecs::Speed>()->getSpeed();

                // Update monster's position based on its speed
                std::pair<int, int> pos = position->getPosition();

                if (speed == 11) {
                    position->set_pos_y(pos.second - speed);
                } else if (speed == 12) {
                    position->set_pos_y(pos.second + speed);
                } else {
                    // Move the monster accordingly
                    position->set_pos_x(pos.first - speed);
                }
            }
            //Boosts (ID 700 to 730)
            if (entity->getEntityId() >= 700 && entity->getEntityId() < 730)
            {
                auto position = entity->getComponent<Ecs::Position>();
                int speed = entity->getComponent<Ecs::Speed>()->getSpeed();

                std::pair<int, int> pos = position->getPosition();

                position->set_pos_y(pos.second + speed);
            }
        }
    }

    void EntityManager::killMonsters()
    {
        for (const auto &entity : getEntsByComp<Ecs::Health>())
        {
            if (entity->getEntityId() >= 5 && entity->getEntityId() < 200)
                deleteEntity(entity->getEntityId());
            if (entity->getEntityId() >= 500 && entity->getEntityId() < 650)
                deleteEntity(entity->getEntityId());
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

    void EntityManager::updateWave()
    {
        static int tick = 0;
        const int interWaveDuration = 300;

        if (this->interWave)
        {
            if (tick >= interWaveDuration)
            {
                this->interWave = false;  // Passer à la prochaine vague
                tick = 0;  // Réinitialiser le compteur
            }
            else
            {
                tick++;  // Incrémenter le compteur de temps
            }
        }
        else
        {
            // Vérifier si le nombre requis de monstres a été tué pour passer à la vague suivante
            int monstersToKillForNextWave = 10;

            if (wave == 1)
                monstersToKillForNextWave = 10;
            if (wave == 2)
                monstersToKillForNextWave = 30;
            if (wave == 3)
                monstersToKillForNextWave = 31;
            if (wave == 4)
                victory = 1;

            if (killedMonstersCount >= monstersToKillForNextWave)
            {
                this->wave++;  // Passer à la vague suivante
                score += 1000;
                killMonsters();
                this->interWave = true;  // Activer le temps entre les vagues
                tick = 0;  // Réinitialiser le compteur
            }
        }
    }
}