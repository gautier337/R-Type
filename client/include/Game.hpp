/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Game
*/

#ifndef GAME_HPP_
    #define GAME_HPP_

#include "Texture.hpp"
#include "SpriteObject.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdio>
#include <set>
#include <chrono>

struct EntityData {
    int id;
    sf::Vector2f position;
    int hp;
    int dead;
    int score;
    int wave;
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
        SpriteObject createAsteroid(int posX, int posY, int id);
        SpriteObject createBoostPack(int posX, int posY, int id);
        SpriteObject createHealthPack(int posX, int posY, int id);
        SpriteObject createParallax(int posX, int posY);
        SpriteObject createShieldPack(int posX, int posY, int id);
        SpriteObject createShieldField(int posX, int posY, int id);

        std::vector<SpriteObject> m_object;
        TextureManager m_textureManager;
        bool m_game_is_over = false;
        int player_hp = 0;
        sf::Texture m_game_is_over_texture, m_texture_hp;
        sf::Sprite m_game_is_over_sprite, m_hp_sprite;
        sf::Font m_font_score;
        sf::Text m_text_score, m_text_wave;

        EntityData m_data;
    private:
};

#endif /* !GAME_HPP_ */
