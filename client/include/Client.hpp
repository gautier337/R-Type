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
#include "Player.hpp"

enum class ConnectionStep {
    WaitingForServer,
    ConnectedToServer,
    GameRunning,
    ConnectionEnded,
};

class Client {
    public:
        Client();
        ~Client();
        ConnectionStep getStatus() const { return m_status;};
        void handleInput(sf::Keyboard::Key key);
        void setStatus(ConnectionStep newStatus) { m_status = newStatus; }
        void run();

    private:
        ConnectionStep m_status;
        sf::RenderWindow m_window;
        Player m_player;
};

#endif /* !CLIENT_HPP_ */
