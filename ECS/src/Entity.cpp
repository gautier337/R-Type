/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Entity
*/

#include "Entity.hpp"

namespace Ecs {

    Entity::Entity(unsigned int id) : _id(id) {}
    Entity::~Entity() {}

    unsigned int Entity::getEntityId() noexcept {
        return _id;
    }

    template <class T>
    bool Entity::hasComponent() noexcept {
        T Comp;

        for (auto &y : _Comps) {
            if (y.get()->getType() == Comp.getType())
                return true;
        }
        return false;
    }

    template <class T>
    bool Entity::removeComponent() noexcept {
        T Comp;

        for (auto it = _Comps.begin(); it != _Comps.end(); it++) {
            if ((*it).get()->getType() == Comp.getType()) {
                _Comps.erase(it);
                return true;
            }
        }
        return false;
    }

    template <class T>
    bool Entity::addComponent(std::shared_ptr<T>& comp) noexcept {
        if (hasComponent<T>())
            return false;
        try {
            _Comps.push_back(comp);
        } catch (std::exception &e) {
            (void)e;
            return false;
        }
        return true;
    }

    template <class T>
    std::shared_ptr<T> Entity::getComponent() noexcept {
        T Comp;

        if (!hasComponent<T>())
            return nullptr;
        for (auto it = _Comps.begin(); it != _Comps.end(); it++) {
            if ((*it).get()->getType() == Comp.getType())
                return std::static_pointer_cast<T>(*it);
        }
        return nullptr;
    }

    template <class T1, class T2, class... Other>
    bool Entity::hasComponents() {
        T1 Comp;

        if (hasComponent<T1>())
            return (true && hasComponents<T2, Other...>());
        return false;
    }

    // Explicit instantiation of templates to be used in Entity.cpp
    template bool Entity::hasComponent<AComponent>() noexcept;
    template bool Entity::removeComponent<AComponent>() noexcept;
    template bool Entity::addComponent<AComponent>(std::shared_ptr<AComponent>&) noexcept;
    template std::shared_ptr<AComponent> Entity::getComponent<AComponent>() noexcept;
    template bool Entity::hasComponents<AComponent>();

}