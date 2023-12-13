/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Damages
*/

#ifndef DAMAGES_HPP_
	#define DAMAGES_HPP_

	#include "AComponent.hpp"

namespace Ecs {

	class Damages : public Ecs::AComponent {
		public:
			Damages(int dmg = 10);
			~Damages();
			inline void setDamage(int dmg) noexcept { _damage = dmg; };
			inline int getDamage() noexcept { return _damage; };
		private:
			int _damage;
	};

}

#endif /* !DAMAGES_HPP_ */
