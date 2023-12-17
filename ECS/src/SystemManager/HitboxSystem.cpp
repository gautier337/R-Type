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
#include "../../include/components/Shoot.hpp"

Ecs::HitboxSystem::HitboxSystem(std::list<std::shared_ptr<Entity>> &entities)
	: ASystem(entities)
{}

void Ecs::HitboxSystem::launch()
{
	for (auto &entity : _Entities) {
		if (entity.get()->hasComponents<Hitbox, Position, Damages, Health>())
			checkForDamages(entity, entity);
	}
}

void Ecs::HitboxSystem::checkForDamages(std::shared_ptr<Entity> entity,
			std::shared_ptr<Entity> otherEntity)
{
	std::pair<int, int> pos = entity.get()->getComponent<Position>()->getPosition();
	std::pair<int, int> otherPos = otherEntity.get()->getComponent<Position>()->getPosition();
	std::pair<int, int> size = entity.get()->getComponent<Hitbox>()->getHitBoxSize();
	std::pair<int, int> otherSize = otherEntity.get()->getComponent<Hitbox>()->getHitBoxSize();

	if (pos.first + size.first >= otherPos.first && pos.first <= otherPos.first + otherSize.first
		&& pos.second + size.second >= otherPos.second && pos.second <= otherPos.second + otherSize.second)
		takeDamages(entity, otherEntity);
}

void Ecs::HitboxSystem::takeDamages(std::shared_ptr<Entity> entity,
			std::shared_ptr<Entity> otherEntity)
{
	int damages = otherEntity.get()->getComponent<Damages>()->getDamage();
	int health = entity.get()->getComponent<Health>()->getHp();

	entity.get()->getComponent<Health>()->setHp(health - damages);
}