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
			Health(int hp = 100);
			~Health();
			inline int getHp() noexcept { return _hp; };
			inline void setHp(int newHp) noexcept { _hp = newHp; };

		private:
			unsigned int _hp;
	};

}

#endif /* !HEALTH_HPP_ */
