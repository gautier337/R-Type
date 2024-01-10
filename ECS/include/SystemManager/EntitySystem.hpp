/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** EntitySystem
*/

#ifndef ENTITYSYSTEM_HPP_
	#define ENTITYSYSTEM_HPP_

	#include "ASystem.hpp"
	#include <list>
	#include <memory>
	#include "Entity.hpp"

namespace Ecs {

    class EntitySystem : public ASystem {
    public:
        EntitySystem(std::list<std::shared_ptr<Entity>> &entities);
        void checkEntitiesState();
		int killedMonstersCount = 0;
		int score = 0;
		int wave = 1;
		bool interWave = true;
		int victory = 0;
		void launch();
		void increaseKilledMonstersCount();
		bool deleteEntity(unsigned int id) noexcept;
		template <class T>
		std::list<std::shared_ptr<Entity>> getEntsByComp()
		{
			std::list<std::shared_ptr<Entity>> entities;
			for (auto &y : _Entities)
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
			for (auto &y : _Entities)
			{
				if (y.get()->hasComponents<Other ...>())
					entities.push_back(y);
			}
			return entities;  // Return a copy, not a reference
		};
    };

}

#endif /* ENTITYSYSTEM_HPP_ */
