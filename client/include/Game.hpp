/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Game
*/

#ifndef GAME_HPP_
    #define GAME_HPP_

#include "Player.hpp"
#include "Texture.hpp"
#include "SpriteObject.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdio>

struct EntityData {
        int id;
        sf::Vector2f position;
        int hp;
    };

class Game {
    public:
        Game();
        ~Game();
        void run(sf::RenderWindow& window, std::string buffer, sf::Time deltaTime);
        SpriteObject createSpriteObject(const EntityData& data);
        void parseBuffer(const std::string& buffer);

        SpriteObject createPlayer(int posX, int posY, int id);
        SpriteObject createSbire(int posX, int posY, int id);
        SpriteObject createBasicSbire(int posX, int posY, int id);
        SpriteObject createBullet(int posX, int posY, int id);

        std::vector<SpriteObject> m_object;
        TextureManager m_textureManager;
    private:
};

#endif /* !GAME_HPP_ */
