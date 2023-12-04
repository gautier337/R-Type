#include "includes/ECSManager.hpp"
#include <iostream>

class PositionComponent : public Component {
public:
    float x;
    float y;
};

class RenderSystem : public System {
public:
    void update() override {
        std::cout << "Rendering entities...\n";
    }
};

int main() {
    ECSManager ecs;

    // Create entities and components
    Entity& entity1 = ecs.createEntity();
    PositionComponent* position1 = ecs.addComponent<PositionComponent>(entity1);
    position1->x = 10.0f;
    position1->y = 20.0f;

    Entity& entity2 = ecs.createEntity();
    PositionComponent* position2 = ecs.addComponent<PositionComponent>(entity2);
    position2->x = 30.0f;
    position2->y = 40.0f;

    // Print entity positions before updating systems
    PositionComponent* pos1 = ecs.getComponent<PositionComponent>(entity1);
    if (pos1) {
        std::cout << "Entity 1 Position (Before Update): (" << pos1->x << ", " << pos1->y << ")\n";
    }

    PositionComponent* pos2 = ecs.getComponent<PositionComponent>(entity2);
    if (pos2) {
        std::cout << "Entity 2 Position (Before Update): (" << pos2->x << ", " << pos2->y << ")\n";
    }

    // Add a system
    ecs.addSystem<RenderSystem>();

    // Update systems
    ecs.updateSystems();

    // Print entity positions after updating systems
    pos1 = ecs.getComponent<PositionComponent>(entity1);
    if (pos1) {
        std::cout << "Entity 1 Position (After Update): (" << pos1->x << ", " << pos1->y << ")\n";
    }

    pos2 = ecs.getComponent<PositionComponent>(entity2);
    if (pos2) {
        std::cout << "Entity 2 Position (After Update): (" << pos2->x << ", " << pos2->y << ")\n";
    }

    return 0;
}
