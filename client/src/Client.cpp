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
    m_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (m_sock < 0) {
        throw std::runtime_error("Erreur lors de la création du socket");
    }

    m_server_addr.sin_family = AF_INET;
    m_server_addr.sin_port = htons(server_port);
    if (inet_pton(AF_INET, server_address, &m_server_addr.sin_addr) <= 0) {
        throw std::runtime_error("Erreur inet_pton");
    }
    m_listenThread = std::thread(&Client::listenToServer, this);
}

Client::~Client()
{
    close(m_sock);
    if (m_listenThread.joinable()) {
        m_listenThread.join();
    }
    close(m_sock);
}

void Client::listenToServer()
{
    while (m_listening) {
        socklen_t addrlen = sizeof(m_server_addr);
        ssize_t recvd = recvfrom(m_sock, m_buffer, m_buffer_size, 0, (struct sockaddr *)&m_server_addr, &addrlen);
        if (recvd > 0) {
            std::cout << "Message reçu du serveur: " << m_buffer << std::endl;
        }
    }
}

int parse_client_id(const char* response)
{
    try {
        std::string resp(response);
        size_t comma_pos = resp.find(',');
        if (comma_pos != std::string::npos) {
            return std::stoi(resp.substr(0, comma_pos));
        }
        throw std::invalid_argument("No comma found in response");
    } catch (std::exception &e) {
        std::cerr << "Erreur lors du parsing de l'ID: " << e.what() << ", response=" << response << std::endl;
        exit(1);
    }
}

void Client::send_message_to_server(const char* message)
{
    sendto(m_sock, message, strlen(message), 0, (const struct sockaddr *)&m_server_addr, sizeof(m_server_addr));
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
                // std::cout << "Scene de jeu" << std::endl;
            }

            if (event.type == sf::Event::Closed)
                m_window.close();
            else if (event.type == sf::Event::KeyPressed)
                handleInput(event.key.code);

            m_window.display();
        }

    }
    send_message_to_server("QUIT");
    std::cout << "Envoi de la commande 'QUIT'" << std::endl;
    close(m_sock);
}

void Client::handleInput(sf::Keyboard::Key key)
{
    switch (key) {
        case sf::Keyboard::Escape: exit(0);
        case sf::Keyboard::Space:
            setScene(ClientScene::GAME);
            send_message_to_server("START");
            // std::cout << "Reçu '" << m_buffer << "' du serveur" << std::endl;
            m_server_client_id = parse_client_id(m_buffer);
            std::cout << "Reçu ID '" << m_server_client_id << "' du serveur" << std::endl;
            break;
        default:
            break;
    }
}