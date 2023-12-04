// Component.cpp
#include "../includes/Component.hpp"

std::size_t Component::getComponentId() {
    static std::size_t nextComponentId = 0;
    return nextComponentId++;
}