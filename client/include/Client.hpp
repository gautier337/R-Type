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
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <thread>

enum class ConnectionStep {
    WaitingForServer,
    ConnectedToServer,
    GameRunning,
    ConnectionEnded,
};

class Client {
    public:
        Client(const char *server_address, int server_port);
        ~Client();
        ConnectionStep getStatus() const { return m_status;};
        void setStatus(ConnectionStep newStatus) { m_status = newStatus; }
        //connection
        void listenToServer();
        void send_message_to_server(const char *message);
        bool started = false;


    private:
        ConnectionStep m_status;
        sf::RenderWindow m_window;
        int sock;
        sockaddr_in server_addr;
        static const size_t buffer_size = 4096;
        char buffer[buffer_size];
        std::thread listenThread;
        bool listening = true;
};

#endif //CLIENT_HPP