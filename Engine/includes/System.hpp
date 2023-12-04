// System.hpp
#pragma once

#include <cstddef>

class System {
public:
    virtual ~System() = default;
    virtual void update() = 0;
};
