/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Client
*/

#include "../include/Client.hpp"

Client::Client(const char *server_address, int server_port): m_window(sf::VideoMode(1920, 1080), "RTYPE CLIENT")
{
    std::cout << "Client created" << std::endl;
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        throw std::runtime_error("Erreur lors de la création du socket");
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    if (inet_pton(AF_INET, server_address, &server_addr.sin_addr) <= 0) {
        throw std::runtime_error("Erreur inet_pton");
    }
    listenThread = std::thread(&Client::listenToServer, this);
}

Client::~Client()
{
    close(sock);
    if (listenThread.joinable()) {
        listenThread.join();
    }
    close(sock);
}

void Client::listenToServer()
{
    while (listening) {
        socklen_t addrlen = sizeof(server_addr);
        ssize_t recvd = recvfrom(sock, buffer, buffer_size, 0, (struct sockaddr *)&server_addr, &addrlen);
        if (recvd > 0) {
            std::cout << "Message reçu du serveur: " << buffer << std::endl;
        }
    }
}

void Client::send_message_to_server(const char* message)
{
    sendto(sock, message, strlen(message), 0, (const struct sockaddr *)&server_addr, sizeof(server_addr));
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