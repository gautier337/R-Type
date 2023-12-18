/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** ShootSystem
*/

#include "../../include/components/Position.hpp"
#include "../../include/components/Shoot.hpp"
#include "../../include/SystemManager/ShootSystem.hpp"

Ecs::ShootSystem::ShootSystem(std::list<std::shared_ptr<Entity>> &entities)
	: ASystem(entities)
{}

void Ecs::ShootSystem::launch()
{
	for (auto &entity : _Entities) {
		if (entity.get()->hasComponents<Shoot, Position>())
			moveMissile(entity);
	}
}

void Ecs::ShootSystem::moveMissile(std::shared_ptr<Entity> entity)
{
	std::pair<int, int> pos = entity.get()->getComponent<Position>()->getPosition();
	entity.get()->getComponent<Position>()->set_pox_x(pos.first +
		entity.get()->getComponent<Shoot>()->getSpeedShoot());
}