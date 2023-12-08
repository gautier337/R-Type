/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** HitboxSystem
*/

#include "HitboxSystem.hpp"
#include "components/HitBox.hpp"
#include "components/Damages.hpp"
#include "components/Health.hpp"
#include "components/AI_ennemies.hpp"
#include "components/Position.hpp"
#include "components/Shoot.hpp"

Ecs::HitboxSystem::HitboxSystem(std::list<std::shared_ptr<Entity>> &entities)
	: ASystem(entities)
{}

void Ecs::HitboxSystem::launch()
{
	std::shared_ptr<Entity> toRemove;
	bool removeAnEntity = false;

	for (auto &entity : _Entities) {
		if (entity.get()->hasComponents<Hitbox, Position, Health>())
            for (auto &otherEntity : _Entities) {
                if (otherEntity.get()->hasComponents<Hitbox, Position, Damages, Shoot>())
                    checkForDamages(entity, otherEntity);
            }
		if (entity.get()->getComponent<Health>()->getHp() < 1) {
			toRemove = entity;
			removeAnEntity = true;
		}
	}
	if (removeAnEntity)
		_Entities.remove(toRemove);
}

void Ecs::HitboxSystem::checkForDamages(std::shared_ptr<Entity> entity,
			std::shared_ptr<Entity> otherEntity)
{
	std::pair<int, int> entityPos =
		entity.get()->getComponent<Position>()->getPosition();
	std::pair<int, int> entityHitbox =
		entity.get()->getComponent<Hitbox>()->getHitBoxSize();
	std::pair<int, int> otherPos =
		otherEntity.get()->getComponent<Position>()->getPosition();
	std::pair<int, int> otherHitbox =
		otherEntity.get()->getComponent<Hitbox>()->getHitBoxSize();

	if (entityPos.first + entityHitbox.first > otherPos.first &&
		entityPos.first < otherPos.first + otherHitbox.first &&
		entityPos.second + entityHitbox.second > otherPos.second &&
		entityPos.second < otherPos.second + otherHitbox.second) {
		takeDamages(entity, otherEntity);
	}
}

void Ecs::HitboxSystem::takeDamages(std::shared_ptr<Entity> entity,
			std::shared_ptr<Entity> otherEntity)
{
	int currentEntityHealth = entity.get()->getComponent<Health>()->getHp();

	currentEntityHealth -= otherEntity.get()->getComponent<Damages>()->getDamage();
	entity.get()->getComponent<Health>()->setHp(currentEntityHealth);
}