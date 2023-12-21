#include "../include/Menu.hpp"
#include "../include/Client.hpp"

Client::Client(const char *server_address, int server_port)
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

Menu::Menu(Client &client) : client(client) {
    window.create(sf::VideoMode(1920, 1080), "R-Type");
    window.setFramerateLimit(60);
    loadAssets();
    setupSprites();
    menuMusic.play();
};

void Menu::updateSprites(sf::Vector2i mouse_pos)
{
    updateSprite(startGame, 780, 365, mouse_pos, START_GAME);
    updateSprite(options, 780, 460, mouse_pos, OPTIONS);
    updateSprite(exit, 780, 555, mouse_pos, EXIT, true);
}

void Menu::render()
{
    window.clear();
    window.draw(background);
    window.draw(startGame);
    window.draw(options);
    window.draw(exit);
    window.display();
}

void Menu::setupSprites()
{
    background.setTexture(textureBackground);
    startGame.setTexture(textureStartGame);
    options.setTexture(textureOptions);
    exit.setTexture(textureExit);
}

void Menu::updateSprite(sf::Sprite& sprite, float posX, float posY, sf::Vector2i mouse_pos, SpriteId spriteId, bool exitButton) {
    sprite.setScale(1.10, 1.10);
    sprite.setPosition(posX, posY);
    if (sprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos))) {
        sprite.setScale(1.15, 1.15);
        sprite.setPosition(posX - 5, posY);
        selectedSprite = spriteId;

        if (exitButton && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            window.close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (selectedSprite == START_GAME && !client.started) {
                client.send_message_to_server("START");
                client.started = true;
            }
        }
    } else if (selectedSprite == spriteId) {
        selectedSprite = NONE;
    }
}

int Menu::run()
{
    Menu menu(client);
    sf::RenderWindow &localWindow = menu.getWindow();

    while (localWindow.isOpen()) {
        sf::Event event;
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(localWindow);

        while (localWindow.pollEvent(event)) {
            if (event.key.code == sf::Keyboard::Escape)
                localWindow.close();
        }
        menu.updateSprites(mouse_pos);
        menu.render();
    }
    return 0;
}

int main() {
    try {
        Client client("127.0.0.1", 8000);
        Menu menu(client);
        return menu.run();
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return -1;
    }
}
