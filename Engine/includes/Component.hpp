// Component.hpp
#pragma once

#include <cstddef>

class Component {
public:
    virtual ~Component() = default;
    static std::size_t getComponentId();
};