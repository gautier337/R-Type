/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** ShootSystem
*/

#ifndef SHOOTSYSTEM_HPP_
	#define SHOOTSYSTEM_HPP_
	#include "ASystem.hpp"


namespace Ecs {

	class ShootSystem : public ASystem {
		public:
			ShootSystem(std::list<std::shared_ptr<Entity>> &entities);
			void launch() final;
		private:
			void moveMissile(std::shared_ptr<Entity> entity);
	};

}

#endif /* !SHOOTSYSTEM_HPP_ */