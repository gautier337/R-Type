/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** HitboxSystem
*/

#include "../../include/SystemManager/HitboxSystem.hpp"
#include "../../include/SystemManager/Entity.hpp"
#include "../../include/components/Speed.hpp"
#include "../../include/components/HitBox.hpp"
#include "../../include/components/Damages.hpp"
#include "../../include/components/Health.hpp"
#include "../../include/components/Position.hpp"
#include "../../include/components/ShootCD.hpp"
#include <iostream>

Ecs::HitboxSystem::HitboxSystem() {}

void Ecs::HitboxSystem::launch(std::list<std::shared_ptr<Entity>> entities)
{
    //print entities
    for (auto it = entities.begin(); it != std::prev(entities.end()); ++it) {
        for (auto it2 = std::next(it); it2 != entities.end(); ++it2) {
            resolveCollisions(*it, *it2, entities);
        }
    }
}

void Ecs::HitboxSystem::resolveCollisions(std::shared_ptr<Entity> entity, std::shared_ptr<Entity> otherEntity, std::list<std::shared_ptr<Entity>> entities)
{
    if (entity->hasComponents<Hitbox, Position, Damages, Health>() &&
        otherEntity->hasComponents<Hitbox, Position, Damages, Health>()) {
        checkForDamages(entity, otherEntity, entities);
        checkForDamages(otherEntity, entity, entities);
    }
}

void Ecs::HitboxSystem::checkForDamages(std::shared_ptr<Entity> entity,
                                        std::shared_ptr<Entity> otherEntity,
                                        std::list<std::shared_ptr<Entity>> entities)
{
    std::pair<int, int> pos = entity->getComponent<Position>()->getPosition();
    std::pair<int, int> otherPos = otherEntity->getComponent<Position>()->getPosition();
    std::pair<int, int> size = entity->getComponent<Hitbox>()->getHitBoxSize();
    std::pair<int, int> otherSize = otherEntity->getComponent<Hitbox>()->getHitBoxSize();

    if (pos.first + size.first >= otherPos.first && pos.first <= otherPos.first + otherSize.first &&
        pos.second + size.second >= otherPos.second && pos.second <= otherPos.second + otherSize.second) {
        // call take damages if the two entities are not player
        if ((entity->getEntityId() >= 1 && entity->getEntityId() <= 4) &&
            (otherEntity->getEntityId() >= 1 && otherEntity->getEntityId() <= 4)) {
            return;
        }
        takeDamages(entity, otherEntity, entities);
    }
}

void Ecs::HitboxSystem::takeDamages(std::shared_ptr<Entity> entity,
                                    std::shared_ptr<Entity> otherEntity,
                                    std::list<std::shared_ptr<Entity>> entities)
{
    int damages = otherEntity->getComponent<Damages>()->getDamage();
    int health = entity->getComponent<Health>()->getHp();

    entity->getComponent<Health>()->setHp(health - damages);
    //check if creator is a player and the other a health pack
    if ((entity->getCreatorId() >= 1 && entity->getCreatorId() <= 4) &&
        (otherEntity->getEntityId() >= 700 && otherEntity->getEntityId() < 710)) {
            //find the player with 4 iterations max
            for (auto it = entities.begin(); it != entities.end(); ++it) {
                if ((*it)->getEntityId() == entity->getCreatorId()) {
                    //add health to the player
                    int playerHealth = (*it)->getComponent<Health>()->getHp();
                    (*it)->getComponent<Health>()->setHp(playerHealth + 5);
                }
            }
    }
    //check if one is a player and the other a health pack
    if ((entity->getEntityId() >= 1 && entity->getEntityId() <= 4) &&
        (otherEntity->getEntityId() >= 700 && otherEntity->getEntityId() < 710)) {
            entity->getComponent<Health>()->setHp(health + 5);
    }
    //check if creator is a player and the other a shoot power up
    if ((entity->getCreatorId() >= 1 && entity->getCreatorId() <= 4) &&
        (otherEntity->getEntityId() >= 710 && otherEntity->getEntityId() < 720)) {
            //find the player with 4 iterations max
            for (auto it = entities.begin(); it != entities.end(); ++it) {
                if ((*it)->getEntityId() == entity->getCreatorId()) {
                    (*it)->getComponent<ShootCD>()->setMultiShoot(true);
                }
            }
    //check if one is a player and the other a shoot power up
    }
    if ((entity->getEntityId() >= 1 && entity->getEntityId() <= 4) &&
        (otherEntity->getEntityId() >= 710 && otherEntity->getEntityId() < 720)) {
            entity->getComponent<ShootCD>()->setMultiShoot(true);
    }
    //check if creator is a player and the other a shield power up
    if ((entity->getCreatorId() >= 1 && entity->getCreatorId() <= 4) &&
        (otherEntity->getEntityId() >= 720 && otherEntity->getEntityId() < 730)) {
            //find the player with 4 iterations max
            for (auto it = entities.begin(); it != entities.end(); ++it) {
                if ((*it)->getEntityId() == entity->getCreatorId()) {
                    (*it)->getComponent<Health>()->setShield(30);
                }
            }
    }
    //check if one is a player and the other a shield power up
    if ((entity->getEntityId() >= 1 && entity->getEntityId() <= 4) &&
        (otherEntity->getEntityId() >= 720 && otherEntity->getEntityId() < 730)) {
            entity->getComponent<Health>()->setShield(30);
    }
}