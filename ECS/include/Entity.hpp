/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
	#define ENTITY_HPP_

	#include <memory>
	#include <list>
	#include <algorithm>
	#include <type_traits>
	#include "../components/AComponent.hpp"

namespace Ecs {
	class Entity {

	public:
		Entity(unsigned int = 0);
		~Entity();
		unsigned int getEntityId() noexcept;

		template <class T>
		bool hasComponent() noexcept;

		template <class T>
		bool removeComponent() noexcept;

		template <class T>
		bool addComponent(std::shared_ptr<T> &Comp) noexcept;

		template <class T>
		std::shared_ptr<T> getComponent() noexcept;

		template <class T1, class T2, class... Other>
		bool hasComponents();

    private:
		std::list<std::shared_ptr<AComponent>> _Comps;
		unsigned int _id;
		template <class T1>
		bool hasComponents()
		{
			T1 _Comps;

			return hasComp<T1>();
		}
	};
}

#endif /* !ENTITY_HPP_ */