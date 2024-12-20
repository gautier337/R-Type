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
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <set>
#include <chrono>
#include <SFML/Audio.hpp>

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
        SpriteObject createKamikazeElite(int posX, int posY, int id);
        SpriteObject createBasicSbire(int posX, int posY, int id);
        SpriteObject createBullet(int posX, int posY, int id);
        SpriteObject createBoss(int posX, int posY, int id);
        SpriteObject createBossHead(int posX, int posY, int id);
        SpriteObject createBossBody(int posX, int posY, int id);
        SpriteObject createAsteroid(int posX, int posY, int id);
        SpriteObject createBoostPack(int posX, int posY, int id);
        SpriteObject createHealthPack(int posX, int posY, int id);
        SpriteObject createParallax(std::string fileName, int posX, int posY);
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
        sf::Music m_music_wave4;
        sf::Music m_music_wave7;

        EntityData m_data;

        Game& operator=(const Game& other) {
            if (this != &other) {
                //copy data
            }
            return *this;
        }
    private:
};

#endif /* !GAME_HPP_ */
