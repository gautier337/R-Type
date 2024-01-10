/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Entity
*/

#include "../../include/SystemManager/Entity.hpp"

namespace Ecs {

    Entity::Entity(unsigned int id, unsigned int creatorId) : _id(id), _creatorId(creatorId) {}

    Entity::~Entity() {}

    unsigned int Entity::getEntityId() noexcept {
        return _id;
    }

    unsigned int Entity::getCreatorId() noexcept {
        return _creatorId;
    }

    // Explicit instantiation of templates to be used in Entity.cpp
    template bool Entity::hasComponent<AComponent>() noexcept;
    template bool Entity::removeComponent<AComponent>() noexcept;
    template bool Entity::addComponent<AComponent>(std::shared_ptr<AComponent>&) noexcept;
    template std::shared_ptr<AComponent> Entity::getComponent<AComponent>() noexcept;
    template bool Entity::hasComponents<AComponent>();

}