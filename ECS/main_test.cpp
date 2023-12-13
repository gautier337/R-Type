#include "include/SystemManager/Entity.hpp"
#include "include/components/Health.hpp"
#include "include/components/Position.hpp"
#include "include/components/Damages.hpp"
#include "include/components/HitBox.hpp"
#include <iostream>

int main () {
    Ecs::Entity entity1(1);
    Ecs::Entity entity2(2);

    // Add Health, Shoot, and Damages components to entities
    auto health1 = std::make_shared<Ecs::Health>(3); // 3 HP for entity 1
    auto damages1 = std::make_shared<Ecs::Damages>(1); // 1 damage for entity 1

    auto health2 = std::make_shared<Ecs::Health>(3); // 3 HP for entity 2
    auto damages2 = std::make_shared<Ecs::Damages>(1); // 1 damage for entity 2

    entity1.addComponent(health1);
    entity1.addComponent(damages1);

    entity2.addComponent(health2);
    entity2.addComponent(damages2);

    // Get Health and Damages components from entities
    auto health1_ = entity1.getComponent<Ecs::Health>();
    auto damages1_ = entity1.getComponent<Ecs::Damages>();

    auto health2_ = entity2.getComponent<Ecs::Health>();
    auto damages2_ = entity2.getComponent<Ecs::Damages>();

    // Print HP before damages
    std::cout << "Entity 1 HP: " << health1_->getHp() << std::endl;
    std::cout << "Entity 2 HP: " << health2_->getHp() << std::endl;

    // Entity 1 damages entity 2
    health2_->setHp(health2_->getHp() - damages1_->getDamage());

    // Entity 2 damages entity 1
    health1_->setHp(health1_->getHp() - damages2_->getDamage());

    // Print HP after damages
    std::cout << "Entity 1 HP: " << health1_->getHp() << std::endl;
    std::cout << "Entity 2 HP: " << health2_->getHp() << std::endl;

    return 0;
}