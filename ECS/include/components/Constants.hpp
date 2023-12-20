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
		SHOOTCD,
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
	const int speedPlayer = 3;
	const int maxWidth = 1920;
	const int maxHeight = 1080;
	const int monstersToKillForWin = 100;
}

#endif /* !CONSTANTS_HPP_ */
