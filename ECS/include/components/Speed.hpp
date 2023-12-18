/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Speed
*/

#ifndef SPEED_HPP_
	#define SPEED_HPP_

	#include "AComponent.hpp"

namespace Ecs {

	class Speed : public AComponent {
		public:
			Speed(int speed = 1);
			~Speed();
			inline int getSpeed() noexcept { return _speed; };
			inline void setSpeed(int newSpeed) noexcept { _speed = newSpeed; };

		private:
			unsigned int _speed;
	};

}

#endif /* !SPEED_HPP_ */
