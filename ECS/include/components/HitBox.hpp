/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** HitBox
*/

#ifndef HITBOX_HPP_
	#define HITBOX_HPP_

	#include <utility>
	#include "AComponent.hpp"

namespace Ecs {

	class Hitbox : public Ecs::AComponent {
		public:
			Hitbox(int height = 1, int width = 1) noexcept;
			~Hitbox();
			inline std::pair<int, int> getHitBoxSize()
			{
				return std::pair<int, int>(_height, _width);
			}
			inline void setHitBoxSize(int height, int width) noexcept
			{
				_height = height;
				_width = width;
			}
			inline void setHitBoxSize(std::pair<int, int> size) noexcept
			{
				_height = size.first;
				_height = size.second;
			}
		private:
            int _width;
            int _height;
	};

}

#endif /* !HITBOX_HPP_ */
