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
		Entity(unsigned int id, unsigned int creatorId = 0);
		~Entity();
		unsigned int getEntityId() noexcept;
		unsigned int getCreatorId() noexcept;
		void setId(unsigned int id) noexcept { _id = id; };

		template <class T>
        bool hasComponent() noexcept {
            T Comp;

            for (auto &y : _Comps) {
                if (y->getType() == Comp.getType())
                    return true;
            }
            return false;
        }

		template <class T>
		bool removeComponent() noexcept {
			T Comp;

			for (auto it = _Comps.begin(); it != _Comps.end(); it++) {
				if ((*it)->getType() == Comp.getType()) {
					_Comps.erase(it);
					return true;
				}
			}
			return false;
		}

		template <class T>
		bool addComponent(std::shared_ptr<T> &Comp) noexcept {
			if (hasComponent<T>())
				return false;
			try {
				_Comps.push_back(Comp);
			} catch (std::exception &e) {
				(void)e;
				return false;
			}
			return true;
		}

		template <class T>
		std::shared_ptr<T> getComponent() noexcept {
			T Comp;

			if (!hasComponent<T>())
				return nullptr;
			for (auto it = _Comps.begin(); it != _Comps.end(); it++) {
				if ((*it)->getType() == Comp.getType())
					return std::dynamic_pointer_cast<T>(*it);
			}
			return nullptr;
		}

		template <class T1, class T2, class... Other>
		bool hasComponents() {
			return hasComponent<T1>() && hasComponents<T2, Other...>();
		}

    private:
		std::list<std::shared_ptr<AComponent>> _Comps;
		unsigned int _id;
		unsigned int _creatorId;
		template <class T1>
		bool hasComponents()
		{
			T1 _Comps;

			return hasComponent<T1>();
		}
	};
}

#endif /* !ENTITY_HPP_ */