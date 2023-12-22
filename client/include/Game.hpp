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
        void run();
        void LoadAllTexture();

    private:
        std::vector<SpriteObject> m_object;
        TextureManager m_textureManager;
};

#endif /* !GAME_HPP_ */
