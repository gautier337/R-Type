// ECSManager.cpp
#include "../includes/ECSManager.hpp"

Entity& ECSManager::createEntity() {
    Entity entity;
    entities.emplace(entity.getId(), std::move(entity));
    return entities[entity.getId()];
}

void ECSManager::destroyEntity(Entity& entity) {
    entities.erase(entity.getId());
    // Add logic to delete associated components and unregister from systems
}

void ECSManager::updateSystems() {
    for (auto& system : systems) {
        system->update();
    }
}
