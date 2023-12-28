/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Client.hpp"

class Menu {
    public:
        Menu() = default;
        ~Menu() = default;
        sf::Sprite m_background;
        sf::Music m_music;
        sf::Sprite m_startGame, m_Exit, m_Options;
        sf::Texture m_startgame, m_exit, m_options;

        void draw(sf::RenderWindow& window) {
            window.draw(m_background);
            std::cout << "On print le bail" << std::endl;
        }

        Menu& operator=(const Menu& other) {
            if (this != &other) {
                //copy data
            }
            return *this;
        }

    private:
};

#endif /* !MENU_HPP_ */
