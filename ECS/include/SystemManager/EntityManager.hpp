/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** EntityManager
*/

#ifndef ENTITYMANAGER_HPP_
	#define ENTITYMANAGER_HPP_

	#include <list>
	#include <memory>
	#include <iostream>
	#include "Entity.hpp"

namespace Ecs {

	class EntityManager {
	private:
		std::list<std::shared_ptr<Entity>> _entityList;

	public:
		EntityManager();
		~EntityManager();
		unsigned int createPlayer() noexcept;
		std::shared_ptr<Entity> createMonster(int entitySize) noexcept;
		std::shared_ptr<Entity> createMissile(int entitySize,  std::pair<int, int> playerPos) noexcept;
		unsigned int addEntity(Entity &entity) noexcept;
		std::shared_ptr<Entity> getEntityById(unsigned int id);
		bool deleteEntity(unsigned int id) noexcept;
		static int random(const int min, const int max) noexcept;
		template <class T>
		std::list<std::shared_ptr<Entity>> getEntsByComp()
		{
			std::list<std::shared_ptr<Entity>> entities;
			for (auto &y : _entityList)
			{
				if (y.get()->hasComponent<T>())
					entities.push_back(y);
			}
			return entities;
		};
		template <class ...Other>
		std::list<std::shared_ptr<Entity>> getEntsByComps()
		{
			std::list<std::shared_ptr<Entity>> entities;
			for (auto &y : _entityList)
			{
				if (y.get()->hasComponents<Other ...>())
					entities.push_back(y);
			}
			return entities;  // Return a copy, not a reference
		};
	};
}

#endif /* !ENTITYMANAGER_HPP_ */
