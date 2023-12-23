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

class Game {
    public:
        Game();
        ~Game();
        void run(sf::RenderWindow& window, std::string buffer, sf::Time deltaTime);
        void LoadAllTexture();

        SpriteObject createPlayer(int posX, int posY);
        SpriteObject createSbire(int posX, int posY);
        SpriteObject createBasicSbire(int posX, int posY);
        SpriteObject createBullet(int posX, int posY);

        std::vector<SpriteObject> m_object;
        TextureManager m_textureManager;
    private:
};

#endif /* !GAME_HPP_ */
