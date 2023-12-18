/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** HitboxSystem
*/

#ifndef HITBOXSYSTEM_HPP_
	#define HITBOXSYSTEM_HPP_
	#include "ASystem.hpp"

namespace Ecs {

	class HitboxSystem : public ASystem {
		public:
			HitboxSystem(std::list<std::shared_ptr<Entity>> &entities);
			void launch() final;
			void takeDamages(std::shared_ptr<Entity> entity,
				std::shared_ptr<Entity> otherEntity);
			void checkForDamages(std::shared_ptr<Entity> entity,
				std::shared_ptr<Entity> otherEntity);
			void resolveCollisions(std::shared_ptr<Entity> entity, std::shared_ptr<Entity> otherEntity);
		private:
	};

}

#endif /* !HITBOXSYSTEM_HPP_ */