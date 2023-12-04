// ECSManager.hpp
#pragma once

#include <cstdint>
#include <unordered_map>
#include <vector>
#include <cstddef>
#include "Entity.hpp"
#include "Component.hpp"
#include "System.hpp"

class ECSManager {
public:
    Entity& createEntity();
    void destroyEntity(Entity& entity);

    template <typename T>
    T* addComponent(Entity& entity) {
        T* component = new T();
        components[entity.getId()][T::getComponentId()] = component;
        return component;
    }

    template <typename T>
    void removeComponent(Entity& entity) {
        auto& componentMap = components[entity.getId()];
        auto it = componentMap.find(T::getComponentId());
        if (it != componentMap.end()) {
            delete it->second;
            componentMap.erase(it);
        }
    }

    template <typename T>
    T* getComponent(Entity& entity) const {
        auto& componentMap = components.at(entity.getId());
        auto it = componentMap.find(T::getComponentId());
        if (it != componentMap.end()) {
            return dynamic_cast<T*>(it->second);
        }
        return nullptr;
    }

    template <typename T>
    void addSystem() {
        systems.push_back(new T());
    }

    static ECSManager& getInstance() {
        static ECSManager instance;
        return instance;
    }

    const std::unordered_map<uint32_t, Entity>& getEntities() const {
        return entities;
    }

    void updateSystems();

private:
    std::unordered_map<uint32_t, Entity> entities;
    std::unordered_map<uint32_t, std::unordered_map<std::size_t, Component*>> components;
    std::vector<System*> systems;
};
