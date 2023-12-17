#include "include/SystemManager/Entity.hpp"
#include "include/SystemManager/EntityManager.hpp"
#include "include/components/Health.hpp"
#include "include/components/Position.hpp"
#include "include/components/Damages.hpp"
#include <iostream>
#include <chrono>
#include <thread>

int main () {
    // Ecs::Entity entity1(1);
    // Ecs::Entity entity2(2);

    // // Add Health, Shoot, and Damages components to entities
    // auto health1 = std::make_shared<Ecs::Health>(3); // 3 HP for entity 1
    // auto damages1 = std::make_shared<Ecs::Damages>(1); // 1 damage for entity 1

    // auto health2 = std::make_shared<Ecs::Health>(3); // 3 HP for entity 2
    // auto damages2 = std::make_shared<Ecs::Damages>(1); // 1 damage for entity 2

    // entity1.addComponent(health1);
    // entity1.addComponent(damages1);

    // entity2.addComponent(health2);
    // entity2.addComponent(damages2);

    // // Get Health and Damages components from entities
    // auto health1_ = entity1.getComponent<Ecs::Health>();
    // auto damages1_ = entity1.getComponent<Ecs::Damages>();

    // auto health2_ = entity2.getComponent<Ecs::Health>();
    // auto damages2_ = entity2.getComponent<Ecs::Damages>();

    // // Print HP before damages
    // std::cout << "Entity 1 HP: " << health1_->getHp() << std::endl;
    // std::cout << "Entity 2 HP: " << health2_->getHp() << std::endl;

    // // Entity 1 damages entity 2
    // health2_->setHp(health2_->getHp() - damages1_->getDamage());

    // // Entity 2 damages entity 1
    // health1_->setHp(health1_->getHp() - damages2_->getDamage());

    // // Print HP after damages
    // std::cout << "Entity 1 HP: " << health1_->getHp() << std::endl;
    // std::cout << "Entity 2 HP: " << health2_->getHp() << std::endl;

    Ecs::EntityManager manager;

    // Create player
    auto player = manager.createPlayer();
    // Create monster
    auto monster = manager.createMonster(1);

    // Add Health, Position, Damages, and HitBox components to entities
    auto health1 = std::make_shared<Ecs::Health>(3); // 3 HP for player
    auto damages1 = std::make_shared<Ecs::Damages>(1); // 1 damage for player
    auto position1 = std::make_shared<Ecs::Position>(0, 0); // Position (0, 0) for player

    auto health2 = std::make_shared<Ecs::Health>(3); // 3 HP for monster
    auto damages2 = std::make_shared<Ecs::Damages>(1); // 1 damage for monster
    auto position2 = std::make_shared<Ecs::Position>(0, 0); // Position (0, 0) for monster

    manager.getEntityById(player)->addComponent(health1);
    manager.getEntityById(player)->addComponent(damages1);
    manager.getEntityById(player)->addComponent(position1);
    monster->addComponent(health1);
    monster->addComponent(damages1);
    monster->addComponent(position1);

    // Loop to print every 1/60 of a second the position of all entities and their HP
    const int updatesPerSecond = 60;
    const std::chrono::milliseconds updateInterval(1000 / updatesPerSecond);

    while (true) {
        // Update player and monster positions and health here

        for (auto& entity : manager.getEntsByComps<Ecs::Position, Ecs::Health>()) {
            std::cout << "Entity " << entity->getEntityId() << " position: (" << entity->getComponent<Ecs::Position>()->getPosition().first << ", " << entity->getComponent<Ecs::Position>()->getPosition().second << ")" << std::endl;
            std::cout << "Entity " << entity->getEntityId() << " HP: " << entity->getComponent<Ecs::Health>()->getHp() << std::endl;
        }

        // Sleep to achieve the desired update rate
        std::this_thread::sleep_for(updateInterval);
    }


    return 0;
}