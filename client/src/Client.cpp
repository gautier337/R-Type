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
            std::cout << "";
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
        return -1;
        // exit(1); // Je mets en commentaire comme ça on exit pas si on a pas l'id on retente juste
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

    m_texture.loadTexture("background", "../assets/galaxy.png");
    m_background.setTexture(m_texture.getTexture("background"));
    // m_background.setScale(sf::Vector2f(0.8, 0.8));

    // Le player
    m_texture.loadTexture("player", "../assets/player.gif");
    // Sbire chelou
    m_texture.loadTexture("basic_sbire", "../assets/basic_sbire.gif");;
    // Sbire normal
    m_texture.loadTexture("sbire", "../assets/sbire.gif");
    // Missile
    m_texture.loadTexture("bullet", "../assets/bullet.gif");
    m_game.m_textureManager = m_texture;
}

void Client::run() {
    setStatus(ClientStep::RunState);
    setScene(ClientScene::MENU);

    sf::Clock clock;

    while (m_window.isOpen()) {
        sf::Time deltaTime = clock.restart();

        // Gestion des événements
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                m_window.close();
            else if (event.type == sf::Event::KeyPressed)
                handleInput(event.key.code);
        }

        // Mise à jour et dessin de la scène
        m_window.clear();
        if (m_currentScene == ClientScene::MENU) {
            m_window.draw(m_menu.m_background);
        } else {
            if (getStatus() != ClientStep::GameRunning) {
                if ((m_server_client_id = parse_client_id(m_buffer)) > 0) {
                    setStatus(ClientStep::GameRunning);
                }
                std::cout << "Reçu ID '" << m_server_client_id << "' du serveur" << std::endl;
            } else {
                m_window.draw(m_background);
                m_game.run(m_window, m_buffer, deltaTime);
                // Mettre à jour et dessiner chaque SpriteObject
            }
        }
        m_window.display();
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
            break;
        default:
            break;
    }
}