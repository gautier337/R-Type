#include "Client.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

#pragma once

#ifndef MENU_HPP
    #define MENU_HPP

class Menu {
    public:
        enum SpriteId {
            NONE,
            START_GAME,
            OPTIONS,
            EXIT
        };

        Menu(Client &client);
        void updateSprites(sf::Vector2i mouse_pos);
        void render();
        int run();
        void setupSprites();
        void updateSprite(sf::Sprite &sprite, float posX, float posY, sf::Vector2i mouse_pos, SpriteId spriteId, bool exitButton = false);
        sf::RenderWindow &getWindow() {
            return window;
        }

    private:
        sf::RenderWindow window;
        Client &client;
        sf::Texture textureBackground, textureStartGame, textureExit, textureOptions;
        sf::Sprite background, startGame, exit, options;
        sf::Music menuMusic;
        SpriteId selectedSprite = NONE;

        void loadAssets() {
            if (!textureStartGame.loadFromFile("../assets/start_game.png") ||
                !textureExit.loadFromFile("../assets/exit.png") ||
                !textureBackground.loadFromFile("../assets/background.png") ||
                !textureOptions.loadFromFile("../assets/options.png") ||
                !menuMusic.openFromFile("../assets/menu_music.ogg")) {
                throw std::runtime_error("Failed to load assets");
            }
        }
};

#endif //MENU_HPP