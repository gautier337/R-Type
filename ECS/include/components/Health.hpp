/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Health
*/

#ifndef HEALTH_HPP_
	#define HEALTH_HPP_

	#include "AComponent.hpp"

namespace Ecs {

	class Health : public AComponent {
		public:
			Health(int hp = 5, int shield = 0, int _maxHp = 5);
			~Health();
			inline int getHp() noexcept { return _hp; };
			inline void setHp(int newHp) noexcept { _hp = newHp; };
			inline int getShield() noexcept { return _shield; };
			inline void setShield(int newShield) noexcept { _shield = newShield; };
			inline int getMaxHp() noexcept { return _maxHp; };
			inline void setMaxHp(int newMaxHp) noexcept { _maxHp = newMaxHp; };

		private:
			unsigned int _hp;
			unsigned int _shield;
			unsigned int _maxHp;
	};

}

#endif /* !HEALTH_HPP_ */
