/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** PlayerSystem
*/

#ifndef PLAYERSYSTEM_HPP_
    #define PLAYERSYSTEM_HPP_

    #include "ASystem.hpp"
    #include "../components/Constants.hpp"
    #include "EntityManager.hpp"
    #include "../components/Position.hpp"

namespace Ecs {

    class PlayerSystem : public ASystem{
        public:
            PlayerSystem(std::list<std::shared_ptr<Entity>> &entities);
            ~PlayerSystem();
            void launch() final;
        protected:
        private:
            void managePlayer(std::shared_ptr<Entity> entity);
            void movePlayer(std::shared_ptr<Entity> entity, int direction);
            void manageShoot(std::shared_ptr<Ecs::Position> pos);
    };
}

#endif /* !PLAYERSYSTEM_HPP_ */
