/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Menu.hpp"

enum class ClientStep {
    InitiationState,
    RunState,
    GameRunning,
    ConnectionEnded,
};

enum class ClientScene {
    MENU,
    GAME,
};

class Client {
    public:
        Client();
        ~Client();
        ClientStep getStatus() const { return m_status;};
        void handleInput(sf::Keyboard::Key key);
        void setStatus(ClientStep newStatus) { m_status = newStatus; }
        void setScene(ClientScene newScene) {m_currentScene = newScene; }
        void run();
        void init();

    private:
        ClientStep m_status;
        ClientScene m_currentScene;
        sf::RenderWindow m_window;
        Game m_game;
        Menu m_menu;
        TextureManager m_texture;
};

#endif /* !CLIENT_HPP_ */
