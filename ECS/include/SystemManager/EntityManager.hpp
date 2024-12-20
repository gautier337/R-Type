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
		bool isGameOver() const;
		int killedMonstersCount;
		int wave = 1;
		bool interWave = true;
		int victory = 0;
		int score = 0;
		void increaseKilledMonstersCount();
		unsigned int createPlayer() noexcept;
		std::shared_ptr<Entity> createMonster(int hp, int dmg, int pos_x, int pos_y, int speedM, int id_min, int id_max, int hitboxX, int hitboxY) noexcept;
		std::shared_ptr<Entity> createMissile(int entityID, int posY = 0) noexcept;
		void updateMissiles();
		void checkEntitiesState();
		void generateMonsters();
		void updateMonsters();
		void updatePlayers();
		void killMonsters();
		void handlePlayerInput(int id, int input) noexcept;
		bool isIdTaken(unsigned int id) const noexcept;
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
		void updateWave();
		void generateBoss1();
		void generateBasicMonster();
		void generateAsteroid();
		void generateKamikaze();
		void generateHealthBoost();
		void generateShootBoost();
		void generateShieldBoost();
		void updateShields(std::shared_ptr<Entity> entity);
	};
}

#endif /* !ENTITYMANAGER_HPP_ */
