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
        auto speed = std::make_shared<Speed>(15);
        auto shootCooldown = std::make_shared<ShootCD>(1);
        player->addComponent(health);
        player->addComponent(damages);
        player->addComponent(position);
        player->addComponent(hitbox);
        player->addComponent(speed);
        player->addComponent(shootCooldown);
        player->getComponent<ShootCD>()->setMultiShoot(false);
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

    void PlayerSystem::updatePlayers()
    {
        static int frameCount = 0;
        const int framesForShootCD = 30; // 0.5 seconds
        const int framesForRegen = 600; // 10 second
        static int frameCountMultiShoot = 0;

        for (const auto &entity : _Entities)
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

    void PlayerSystem::updateShields(std::shared_ptr<Entity> entity)
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
            _Entities.push_back(shield);
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
            _Entities.push_back(shield);
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
            _Entities.push_back(shield);
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
            _Entities.push_back(shield);
        } else if (entity->getEntityId() == 4 && getEntityById(804) != nullptr) {
            getEntityById(804)->getComponent<Ecs::Health>()->setHp(entity->getComponent<Ecs::Health>()->getShield());
            getEntityById(804)->getComponent<Ecs::Position>()->set_pos_x(entity->getComponent<Ecs::Position>()->getPosition().first + 30);
            getEntityById(804)->getComponent<Ecs::Position>()->set_pos_y(entity->getComponent<Ecs::Position>()->getPosition().second);
        }
    }

    std::shared_ptr<Entity> PlayerSystem::createMissile(int entityID, int posY) noexcept
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

        auto missile = std::make_shared<Entity>(id);
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
        updatePlayers();
    }

}