/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** HitboxSystem
*/

#include "../../include/SystemManager/HitboxSystem.hpp"
#include "../../include/components/HitBox.hpp"
#include "../../include/components/Damages.hpp"
#include "../../include/components/Health.hpp"
#include "../../include/components/Position.hpp"

Ecs::HitboxSystem::HitboxSystem(std::list<std::shared_ptr<Entity>> &entities)
    : ASystem(entities)
{}

void Ecs::HitboxSystem::launch()
{
    for (auto it = _Entities.begin(); it != std::prev(_Entities.end()); ++it) {
        for (auto it2 = std::next(it); it2 != _Entities.end(); ++it2) {
            resolveCollisions(*it, *it2);
        }
    }
}

void Ecs::HitboxSystem::resolveCollisions(std::shared_ptr<Entity> entity, std::shared_ptr<Entity> otherEntity)
{
    if (entity->hasComponents<Hitbox, Position, Damages, Health>() &&
        otherEntity->hasComponents<Hitbox, Position, Damages, Health>()) {
        checkForDamages(entity, otherEntity);
        checkForDamages(otherEntity, entity);
    }
}

void Ecs::HitboxSystem::checkForDamages(std::shared_ptr<Entity> entity,
                                        std::shared_ptr<Entity> otherEntity)
{
    std::pair<int, int> pos = entity->getComponent<Position>()->getPosition();
    std::pair<int, int> otherPos = otherEntity->getComponent<Position>()->getPosition();
    std::pair<int, int> size = entity->getComponent<Hitbox>()->getHitBoxSize();
    std::pair<int, int> otherSize = otherEntity->getComponent<Hitbox>()->getHitBoxSize();

    if (pos.first + size.first >= otherPos.first && pos.first <= otherPos.first + otherSize.first &&
        pos.second + size.second >= otherPos.second && pos.second <= otherPos.second + otherSize.second) {
        takeDamages(entity, otherEntity);
    }
}

void Ecs::HitboxSystem::takeDamages(std::shared_ptr<Entity> entity,
                                    std::shared_ptr<Entity> otherEntity)
{
    int damages = otherEntity->getComponent<Damages>()->getDamage();
    int health = entity->getComponent<Health>()->getHp();

    entity->getComponent<Health>()->setHp(health - damages);
}