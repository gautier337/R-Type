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
			ShootCD(float cd = 1);
			~ShootCD();
			inline float getCd() noexcept { return _cd; };
			inline void setCd(int newCd) noexcept { _cd = newCd; };
            inline void decreaseCd() noexcept { _cd--; };
			inline bool getMultiShoot() noexcept { return _multiShoot; };
			inline void setMultiShoot(bool multiShoot) noexcept { _multiShoot = multiShoot; };

		private:
			float _cd;
			bool _multiShoot;
	};

}

#endif /* !SHOOTCD_HPP_ */
