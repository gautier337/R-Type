/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** ShootCD
*/

#ifndef SHOOTCD_HPP_
	#define SHOOTCD_HPP_

	#include "AComponent.hpp"

namespace Ecs {

	class ShootCD : public AComponent {
		public:
			ShootCD(int cd = 1);
			~ShootCD();
			inline int getCd() noexcept { return _cd; };
			inline void setCd(int newCd) noexcept { _cd = newCd; };
            inline void decreaseCd() noexcept { _cd--; };

		private:
			unsigned int _cd;
	};

}

#endif /* !SHOOTCD_HPP_ */
