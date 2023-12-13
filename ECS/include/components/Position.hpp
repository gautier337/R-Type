/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Position
*/

#ifndef POSITION_HPP_
	#define POSITION_HPP_

	#include <utility>
	#include "AComponent.hpp"

namespace Ecs {

	class Position : public AComponent {
		public:
			Position(int X = 0, int Y = 0);
			~Position();
			inline void set_pox_x(int X) noexcept { _x = X; };
			inline void set_pox_y(int Y) noexcept { _y = Y; };
			std::pair<int, int> getPosition() noexcept { return (std::make_pair(_x, _y)); };

		private:
			int _x;
			int _y;
	};

}
#endif /* !POSITION_HPP_ */
