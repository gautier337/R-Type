/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** MonsterSystem
*/

#ifndef MONSTERSYSTEM_HPP_
	#define MONSTERSYSTEM_HPP_

	#include "ASystem.hpp"
	#include <list>
	#include <memory>
	#include "EntitySystem.hpp"
	#include "../../include/components/Position.hpp"
	#include "../../include/components/Health.hpp"
	#include "../../include/components/Damages.hpp"
	#include "../../include/components/ShootCD.hpp"
	#include "../../include/components/Speed.hpp"
	#include "../../include/components/HitBox.hpp"
	#include "../../include/components/Constants.hpp"
	#include "../../include/components/Position.hpp"

namespace Ecs {

    class MonsterSystem : public ASystem {
    public:
        MonsterSystem(std::list<std::shared_ptr<Entity>> &entities, EntitySystem& entitySystem, bool solo);

        std::shared_ptr<Entity> createMonster(int hp, int dmg, int pos_x, int pos_y, int speedM, int id_min, int id_max, int hitboxX, int hitboxY) noexcept;
        void generateMonsters();
        void updateMonsters();
		bool isIdTaken(unsigned int id) const noexcept;
		std::shared_ptr<Entity> getEntityById(unsigned int id);
		int random(const int min, const int max) noexcept;
		std::shared_ptr<Entity> createMissile(int entityID, int posY = 0) noexcept;
		void killMonsters();
		bool deleteEntity(unsigned int id) noexcept;
		void updateWave();
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
		void launch() final;
		void generateBoss1();
		void generateBoss2();
		void generateBasicMonster();
		void generateEliteMonster();
		void generateSnakeBoss();
		void generateAsteroid();
		void generateKamikaze();
		void generateEliteKamikaze();
		void generateHealthBoost();
		void generateShootBoost();
		void generateShieldBoost();
		void generateAI();
		void updateShields(std::shared_ptr<Entity> entity);
	private:
		EntitySystem& _entitySystem;
		bool _solo = false;
    };

}

#endif /* MONSTERSYSTEM_HPP_ */
