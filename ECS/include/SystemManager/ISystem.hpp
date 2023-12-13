/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** ISystem
*/

#ifndef ISYSTEM_HPP_
	#define ISYSTEM_HPP_

namespace Ecs {
	class ISystem {
	public:
		virtual ~ISystem() = default;
		virtual void launch() = 0;

	protected:
	};
}

#endif /* !ISYSTEM_HPP_ */
