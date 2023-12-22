/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Client
*/

#include "../include/Client.hpp"

Client::Client() : m_window(sf::VideoMode(1920, 1080), "RTYPE CLIENT")
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
    m_texture = TextureManager();

    m_texture.loadTexture("menu", "../assets/background.png");
    m_menu.m_background.setTexture(m_texture.getTexture("menu"));
    m_menu.m_background.setScale(sf::Vector2f(0.8, 0.8));

}

void Client::run()
{
    setStatus(ClientStep::RunState);
    setScene(ClientScene::MENU);

    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            m_window.clear();

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

            m_window.display();
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