/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** PlayerSystem
*/

#ifndef PLAYERSYSTEM_HPP_
    #define PLAYERSYSTEM_HPP_

	#include "ASystem.hpp"
	#include <list>
	#include <memory>
	#include "Entity.hpp"
	#include "../../include/SystemManager/EntityManager.hpp"
	#include "../../include/components/Position.hpp"
	#include "../../include/components/Health.hpp"
	#include "../../include/components/Damages.hpp"
	#include "../../include/components/ShootCD.hpp"
	#include "../../include/components/Speed.hpp"
	#include "../../include/components/HitBox.hpp"
	#include "../../include/components/Constants.hpp"
	#include <cmath>

namespace Ecs {

    class PlayerSystem : public ASystem
	{
        public:
            PlayerSystem(std::list<std::shared_ptr<Entity>> &entities);
            ~PlayerSystem();
            void launch() final;
            unsigned int createPlayer() noexcept;
            void handlePlayerInput(int id, int input) noexcept;
			bool isIdTaken(unsigned int id) const noexcept;
			std::shared_ptr<Entity> getEntityById(unsigned int id);
			std::shared_ptr<Entity> createMissile(int entityID, int posY = 0) noexcept;
			void updatePlayers();
			void updateShields(std::shared_ptr<Entity> entity);
    };
}

#endif /* !PLAYERSYSTEM_HPP_ */
