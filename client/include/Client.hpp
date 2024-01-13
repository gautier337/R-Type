/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Client
*/

#pragma once

#ifndef CLIENT_HPP
    #define CLIENT_HPP

#include "Game.hpp"
#include "Menu.hpp"
#include "Options.hpp"
#include "SpriteObject.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <thread>
#include <string>
#include <stdexcept>
#include <chrono>
#include <regex>
#include <sstream>

enum class ClientStep {
    InitiationState,
    RunState,
    GameRunning,
    ConnectionEnded,
};

enum class ClientScene {
    MENU,
    GAME,
    OPTIONS,
    GAME_OVER,
};

class Client {
    public:
        Client(const char *server_address, int server_port);
        ~Client();
        ClientStep getStatus() const { return m_status;};
        void setStatus(ClientStep newStatus) { m_status = newStatus; }

        void handleInput();
        void setScene(ClientScene newScene) {m_currentScene = newScene; }
        void run();
        void init();
        //connection
        void listenToServer();
        void display_options();
        void display_menu();
        void send_message_to_server(const char *message);
        void checkButtonHover(sf::Sprite& button, const sf::Vector2i& mousePos);
        void handleMouse(sf::Mouse::Button button);
        void handleButtonHover(sf::Vector2i mousePos);

        sf::Music m_bullet_sound;
    private:
        std::array<bool, sf::Keyboard::KeyCount> keyStatus;
        std::array<std::chrono::steady_clock::time_point, sf::Keyboard::KeyCount> lastKeyPressTime;
        const std::chrono::milliseconds keyPressInterval{90};
        sf::RenderWindow m_window;
        ClientStep m_status;
        ClientScene m_currentScene;

        Game m_game;
        Menu m_menu;
        Options m_options;
        SpriteObject m_parallax;
        TextureManager m_texture;
        int client_id = 0;
        bool game_started = false;
        int m_sock;
        sockaddr_in m_server_addr;

        static const size_t m_buffer_size = 4096;
        char m_buffer[m_buffer_size];
        std::thread m_listenThread;
        bool m_listening = true;
        bool m_parallax_wave4 = false;
        bool m_parallax_wave7 = false;
};

#endif //CLIENT_HPP