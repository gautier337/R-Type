/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** MonsterSystem
*/

#include "../../include/SystemManager/MonsterSystem.hpp"

namespace Ecs {

    MonsterSystem::MonsterSystem(std::list<std::shared_ptr<Entity>> &entities, EntitySystem& entitySystem)
        : ASystem(entities), _entitySystem(entitySystem) {}

    std::shared_ptr<Entity> MonsterSystem::createMonster(int hp, int dmg, int pos_x, int pos_y, int speedM, int id_min, int id_max, int hitboxX, int hitboxY) noexcept {
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
        _Entities.push_back(monster);
        return monster;
    }

    void MonsterSystem::generateBoss1()
    {
        createMonster(50, 5, 1200, 540, 2, 600, 601, 160, 210);
    }

    void MonsterSystem::generateBasicMonster()
    {
        int xPos = random(1300, 1500);
        int yPos = random(100, 980);
        createMonster(3, 1, xPos, yPos, 2, 5, 200, 33, 34);
    }

    void MonsterSystem::generateAsteroid()
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

    void MonsterSystem::generateKamikaze()
    {
        int xPos = random(1100, 1300);
        int yPos = random(100, 980);
        createMonster(1, 10, xPos, yPos, 8, 500, 600, 33, 32);
    }

    void MonsterSystem::generateHealthBoost()
    {
        int xPos = random(100, 1000);
        int yPos = -100;
        createMonster(1, 1, xPos, yPos, 2, 700, 710, 15, 15);
    }

    void MonsterSystem::generateShootBoost()
    {
        int xPos = random(100, 1000);
        int yPos = -100;
        createMonster(1, 1, xPos, yPos, 2, 710, 720, 15, 15);
    }

    void MonsterSystem::generateShieldBoost()
    {
        int xPos = random(100, 1000);
        int yPos = -100;
        createMonster(1, 1, xPos, yPos, 2, 720, 730, 15, 15);
    }

    void MonsterSystem::generateMonsters()
    {
        static int frameCount = 0;
        const int framesPerMonster = 180; // 60 frames per second * 3 seconds

        // Generate a monster every 3 seconds
        if (frameCount % framesPerMonster == 0) {

            // Generate a random number between 0 and 9
            int randomNum = random(0, 10);

            if (_entitySystem.wave == 1) {
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
            } else if (_entitySystem.wave == 2) {
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
            } else if (_entitySystem.wave == 3) {
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

    void MonsterSystem::updateWave() {
        static int tick = 0;
        const int interWaveDuration = 300;

        if (_entitySystem.interWave)
        {
            if (tick >= interWaveDuration)
            {
                _entitySystem.interWave = false;  // Passer à la prochaine vague
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

            if (_entitySystem.wave == 1)
                monstersToKillForNextWave = 10;
            if (_entitySystem.wave == 2)
                monstersToKillForNextWave = 30;
            if (_entitySystem.wave == 3)
                monstersToKillForNextWave = 31;
            if (_entitySystem.wave == 4)
                _entitySystem.victory = 1;

            if (_entitySystem.killedMonstersCount >= monstersToKillForNextWave)
            {
                _entitySystem.wave++;  // Passer à la vague suivante
                _entitySystem.score += 1000;
                killMonsters();
                _entitySystem.interWave = true;  // Activer le temps entre les vagues
                tick = 0;  // Réinitialiser le compteur
            }
        }
    }

    std::shared_ptr<Entity> MonsterSystem::createMissile(int entityID) noexcept {
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


    void MonsterSystem::updateMonsters()
    {
        for (const auto& entity : _Entities) {
            //Basic
            if (entity->getEntityId() >= 5 && entity->getEntityId() < 200) {
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
                for (const auto& entity : _Entities)
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

    bool MonsterSystem::isIdTaken(unsigned int id) const noexcept {
        return std::any_of(_Entities.begin(), _Entities.end(), [id](const std::shared_ptr<Entity>& entity) {
            return entity->getEntityId() == id;
        });
    }

	std::shared_ptr<Entity> MonsterSystem::getEntityById(unsigned int id)
    {
        for (auto &y : _Entities)
        {
            if (y.get()->getEntityId() == id)
                return y;
        }
        return nullptr;
    }

	int MonsterSystem::random(const int min, const int max) noexcept
	{
		return rand() % (max - min) + min;
	}

    bool MonsterSystem::deleteEntity(unsigned int id) noexcept
    {
        for (auto &y : _Entities)
        {
            if (y.get()->getEntityId() == id)
            {
                _Entities.remove(y);
                return true;
            }
        }
        return false;
    }

    void MonsterSystem::killMonsters()
    {
        for (const auto &entity : getEntsByComp<Ecs::Health>())
        {
            if (entity->getEntityId() >= 5 && entity->getEntityId() < 200)
                deleteEntity(entity->getEntityId());
            if (entity->getEntityId() >= 500 && entity->getEntityId() < 650)
                deleteEntity(entity->getEntityId());
        }
    }

    void MonsterSystem::launch() {
        updateMonsters();
        updateWave();
        if (_entitySystem.interWave == false) {
            generateMonsters();
        }
    }

}
