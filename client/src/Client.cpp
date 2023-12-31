/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Client
*/

#include "../include/Client.hpp"
#include <iostream>

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
    m_options = Options();
    m_texture = TextureManager();

    //menu
    m_texture.loadTexture("menu", "../assets/background.png");
    m_texture.loadTexture("startgame", "../assets/start_game.png");
    m_texture.loadTexture("exit", "../assets/exit.png");
    m_texture.loadTexture("options", "../assets/options.png");
    m_menu.m_background.setTexture(m_texture.getTexture("menu"));

    m_menu.m_startGame.setTexture(m_texture.getTexture("startgame"));
    m_menu.m_startGame.setPosition(630, 295);
    m_menu.m_startGame.setScale(sf::Vector2f(0.85, 0.85));

    m_menu.m_Options.setTexture(m_texture.getTexture("options"));
    m_menu.m_Options.setPosition(630, 370);
    m_menu.m_Options.setScale(sf::Vector2f(0.85, 0.85));

    m_menu.m_Exit.setTexture(m_texture.getTexture("exit"));
    m_menu.m_Exit.setPosition(630, 445);
    m_menu.m_Exit.setScale(sf::Vector2f(0.85, 0.85));

    m_menu.m_background.setScale(sf::Vector2f(0.8, 0.8));
    if (!m_menu.m_music.openFromFile("../assets/menu_music.ogg")) {
        std::cerr << "Failed to load menu music" << std::endl;
        std::exit(1);
    } else
        std::cout << "Menu music loaded successfully" << std::endl;

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

    //scene options
    m_options.m_texture_background_options.loadFromFile("../assets/background_options.png");
    m_options.m_background_options.setTexture(m_options.m_texture_background_options);
    m_options.m_background_options.setScale(sf::Vector2f(0.8, 0.8));

    m_options.m_texture_off_sound.loadFromFile("../assets/off_button.png");
    m_options.m_off_sound.setTexture(m_options.m_texture_off_sound);
    m_options.m_off_sound.setPosition(0, 325);
    m_options.m_off_sound.setScale(sf::Vector2f(0.85, 0.85));

    m_options.m_texture_on_sound.loadFromFile("../assets/on_button.png");
    m_options.m_on_sound.setTexture(m_options.m_texture_on_sound);
    m_options.m_on_sound.setPosition(160, 325);
    m_options.m_on_sound.setScale(sf::Vector2f(0.85, 0.85));

    m_options.m_texture_30fps.loadFromFile("../assets/30fps.png");
    m_options.m_30fps.setTexture(m_options.m_texture_30fps);
    m_options.m_30fps.setPosition(1390, 320);
    m_options.m_30fps.setScale(sf::Vector2f(0.85, 0.85));

    m_options.m_texture_60fps.loadFromFile("../assets/60fps.png");
    m_options.m_60fps.setTexture(m_options.m_texture_60fps);
    m_options.m_60fps.setPosition(1240, 320);
    m_options.m_60fps.setScale(sf::Vector2f(0.85, 0.85));

    m_options.m_texture_1920.loadFromFile("../assets/1920x1080.png");
    m_options.m_button1920.setTexture(m_options.m_texture_1920);
    m_options.m_button1920.setPosition(690, 345);
    m_options.m_button1920.setScale(sf::Vector2f(0.85, 0.85));

    m_options.m_texture_3024.loadFromFile("../assets/3024x1964.png");
    m_options.m_button3024.setTexture(m_options.m_texture_3024);
    m_options.m_button3024.setPosition(690, 390);
    m_options.m_button3024.setScale(sf::Vector2f(0.85, 0.85));
}

void Client::checkButtonHover(sf::Sprite& button, const sf::Vector2i& mousePos)
{
    sf::FloatRect bounds = button.getGlobalBounds();
    float x = bounds.left + bounds.width / 2;
    float y = bounds.top + bounds.height / 2;
    if (bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
        button.setScale(0.9f, 0.9f);
        button.setPosition(x - button.getGlobalBounds().width / 2, y - button.getGlobalBounds().height / 2);
    } else {
        button.setScale(0.85f, 0.85f);
        button.setPosition(x - button.getGlobalBounds().width / 2, y - button.getGlobalBounds().height / 2);
    }
}

void Client::run()
{
    if (!m_window.isOpen()) {
        std::cerr << "Window" << std::endl;
        return;
    }

    setStatus(ClientStep::RunState);
    setScene(ClientScene::MENU);
    sf::Clock clock;

    while (m_window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                handleInput(event.key.code);
                if (event.key.code == sf::Keyboard::Enter) {
                    setScene(ClientScene::GAME);
                }
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
                    sf::FloatRect exitBounds = m_menu.m_Exit.getGlobalBounds();
                    sf::FloatRect startGameBounds = m_menu.m_startGame.getGlobalBounds();
                    sf::FloatRect optionsBounds = m_menu.m_Options.getGlobalBounds();
                    // sf::FloatRect fps30Bounds = m_options.m_30fps.getGlobalBounds();
                    // sf::FloatRect fps60Bounds = m_options.m_60fps.getGlobalBounds();
                    sf::FloatRect soundOnBounds = m_options.m_on_sound.getGlobalBounds();
                    sf::FloatRect soundOffBounds = m_options.m_off_sound.getGlobalBounds();
                    // sf::FloatRect button1920Bounds = m_options.m_button1920.getGlobalBounds();
                    // sf::FloatRect button3024Bounds = m_options.m_button3024.getGlobalBounds();

                    if (exitBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        m_window.close();
                        std::exit(0);
                    }
                    if (startGameBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        setScene(ClientScene::GAME);
                        send_message_to_server("START");
                    }
                    if (optionsBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        setScene(ClientScene::OPTIONS);
                    }
                    // if (fps30Bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    //     m_game.setFps(30);
                    // }
                    // if (fps60Bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    //     m_game.setFps(60);
                    // }
                    if (soundOffBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        m_menu.m_music.setVolume(0);
                    }
                    if (soundOnBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        m_menu.m_music.setVolume(100);
                    }
                }
            }
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
        checkButtonHover(m_menu.m_startGame, mousePos);
        checkButtonHover(m_menu.m_Exit, mousePos);
        checkButtonHover(m_menu.m_Options, mousePos);
        checkButtonHover(m_options.m_button1920, mousePos);
        checkButtonHover(m_options.m_button3024, mousePos);
        checkButtonHover(m_options.m_30fps, mousePos);
        checkButtonHover(m_options.m_60fps, mousePos);
        checkButtonHover(m_options.m_off_sound, mousePos);
        checkButtonHover(m_options.m_on_sound, mousePos);

        if (m_window.isOpen()) {
            m_window.clear();
            if (m_currentScene == ClientScene::MENU) {
                if (m_menu.m_music.getStatus() != sf::SoundSource::Status::Playing)
                    m_menu.m_music.play();
                m_window.draw(m_menu.m_background);
                m_window.draw(m_menu.m_startGame);
                m_window.draw(m_menu.m_Exit);
                m_window.draw(m_menu.m_Options);
            } else if (m_currentScene == ClientScene::GAME) {
                m_window.draw(m_background);
                m_game.run(m_window, m_buffer, deltaTime);
            } else if (m_currentScene == ClientScene::OPTIONS) {
                m_window.draw(m_options.m_background_options);
                m_window.draw(m_options.m_30fps);
                m_window.draw(m_options.m_60fps);
                m_window.draw(m_options.m_button1920);
                m_window.draw(m_options.m_button3024);
                m_window.draw(m_options.m_off_sound);
                m_window.draw(m_options.m_on_sound);
            }
            m_window.display();
        }
    }
    send_message_to_server("QUIT");
    std::cout << "Sending 'QUIT' command" << std::endl;
    close(m_sock);
}

void Client::handleInput(sf::Keyboard::Key key)
{
    switch (key) {
        case sf::Keyboard::Escape:
            setScene(ClientScene::MENU);
            break;
        case sf::Keyboard::Q: exit(0);
        case sf::Keyboard::Enter:
            setScene(ClientScene::GAME);
            send_message_to_server("START");
            break;
        case sf::Keyboard::Space:
            send_message_to_server("SHOOT");
            break;
        case sf::Keyboard::Left:
            send_message_to_server("LEFT");
            break;
        case sf::Keyboard::Right:
            send_message_to_server("RIGHT");
            break;
        case sf::Keyboard::Up:
            send_message_to_server("UP");
            break;
        case sf::Keyboard::Down:
            send_message_to_server("DOWN");
            break;
        default:
            break;
    }
}