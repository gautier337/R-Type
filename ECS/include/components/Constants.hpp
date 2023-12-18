/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Constants
*/

#ifndef CONSTANTS_HPP_
#define CONSTANTS_HPP_

#include <utility>

namespace Constants
{
	enum Comps
	{
		HEALTH,
		DRAWABLE,
		HITBOX,
		POSITION,
		DAMAGES,
		SPEEDSHOOT,
		SPEED,
		WEAPON,
		AI
	};

	enum EVENT {
        MOVE,
        SHOOT,
        QUIT,
    };

    enum DIRECTION {
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

	const int damage_missile = 10;
	const int speedShoot = 3;
}

#endif /* !CONSTANTS_HPP_ */
