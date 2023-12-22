/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Client
*/

#pragma once

#ifndef CLIENT_HPP
    #define CLIENT_HPP

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Menu.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <thread>

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
        Client(const char *server_address, int server_port);
        ~Client();
        ClientStep getStatus() const { return m_status;};
        void setStatus(ClientStep newStatus) { m_status = newStatus; }

        void handleInput(sf::Keyboard::Key key);
        void setScene(ClientScene newScene) {m_currentScene = newScene; }
        void run();
        void init();
        //connection
        void listenToServer();
        void send_message_to_server(const char *message);
        bool started = false;


    private:
        ClientStep m_status;
        ClientScene m_currentScene;
        sf::RenderWindow m_window;
        Game m_game;
        Menu m_menu;
        TextureManager m_texture;
        int sock;
        sockaddr_in server_addr;
        static const size_t buffer_size = 4096;
        char buffer[buffer_size];
        std::thread listenThread;
        bool listening = true;
};

#endif //CLIENT_HPP