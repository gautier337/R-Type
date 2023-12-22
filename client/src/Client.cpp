/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Client
*/

#include "../include/Client.hpp"

Client::Client() : m_window(sf::VideoMode(800, 600), "RTYPE CLIENT")
{
}

Client::~Client()
{
}

////////////////////////////////////////////////////////////
//
// Create Menu / Game Class / Init texture vector and sprite vector
//
////////////////////////////////////////////////////////////
void Client::init()
{
    setStatus(ClientStep::InitiationState);
    m_game = Game();
    m_menu = Menu();

    TextureManager texture = TextureManager();

    texture.loadTexture("menu", "../assets/background.png");
    m_menu.m_background.setTexture(texture.getTexture("menu"));
    m_menu.m_background.setPosition(0, 0);
}

void Client::run()
{
    setStatus(ClientStep::RunState);
    setScene(ClientScene::MENU);

    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (m_currentScene == ClientScene::MENU) {
                m_window.draw(m_menu.m_background);
            } else {
                m_game.run();
                std::cout << "Scene de jeu" << std::endl;
            }

            if (event.type == sf::Event::Closed)
                m_window.close();
            else if (event.type == sf::Event::KeyPressed)
                handleInput(event.key.code);
        }
    }
}

void Client::handleInput(sf::Keyboard::Key key)
{
    switch (key) {
        case sf::Keyboard::Escape: exit(0);
        case sf::Keyboard::Space: setScene(ClientScene::GAME);
        default:
            break;
    }
}