// Entity.hpp
#pragma once

#include <cstdint>

class Entity {
    public:
        Entity() : id(++nextId) {}
        uint32_t getId() const { return id; }

    private:
        uint32_t id;
        static uint32_t nextId;
};
