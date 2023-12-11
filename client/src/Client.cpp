/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Client
*/

#include "../include/Client.hpp"

Client::Client() : m_window(sf::VideoMode(800, 600), "RTYPE CLIENT"), m_player(400, 300, 5.0f)
{
}

Client::~Client()
{
}

// Game::Game() : window(sf::VideoMode(800, 600), "Mon jeu avec ECS"), player(400, 300, 5.0f) {}

void Client::run()
{
    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                m_window.close();
            else if (event.type == sf::Event::KeyPressed)
                handleInput(event.key.code);
        }

        m_player.update();

        m_window.clear();
        m_player.draw(m_window);
        m_window.display();
    }
}

void Client::handleInput(sf::Keyboard::Key key)
{
    switch (key) {
        case sf::Keyboard::Left: m_player.accumulateVelocity(-m_player.getSpeed(), 0);
            break;
        case sf::Keyboard::Right: m_player.accumulateVelocity(m_player.getSpeed(), 0);
            break;
        case sf::Keyboard::Up: m_player.accumulateVelocity(0, -m_player.getSpeed());
            break;
        case sf::Keyboard::Down: m_player.accumulateVelocity(0, m_player.getSpeed());
            break;
        case sf::Keyboard::Escape: exit(0);
        default:
            break;
    }
}