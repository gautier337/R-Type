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
    int dead;
    int score;
};

class Game {
    public:
        Game();
        ~Game();
        void run(sf::RenderWindow& window, std::string buffer, sf::Time deltaTime, SpriteObject m_parallax);
        // SpriteObject createSpriteObject(const EntityData& data);
        void parseBuffer(const std::string& buffer);

        SpriteObject createPlayer(int posX, int posY, int id);
        SpriteObject createSbire(int posX, int posY, int id);
        SpriteObject createKamikaze(int posX, int posY, int id);
        SpriteObject createBasicSbire(int posX, int posY, int id);
        SpriteObject createBullet(int posX, int posY, int id);
        SpriteObject createBoss(int posX, int posY, int id);
        SpriteObject createParallax(int posX, int posY);

        std::vector<SpriteObject> m_object;
        TextureManager m_textureManager;
        bool m_game_is_over = false;
        sf::Texture m_game_is_over_texture, m_texture_hp;
        sf::Sprite m_game_is_over_sprite, m_hp_sprite;
        sf::Font m_font_score;
        sf::Text m_text_score;

        EntityData m_data;
    private:
};

#endif /* !GAME_HPP_ */
