#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

class Client {
    public:
        Client(const char* server_address, int server_port) {
            sock = socket(AF_INET, SOCK_DGRAM, 0);
            if (sock < 0) {
                throw std::runtime_error("Erreur lors de la création du socket");
            }

            server_addr.sin_family = AF_INET;
            server_addr.sin_port = htons(server_port);
            if (inet_pton(AF_INET, server_address, &server_addr.sin_addr) <= 0) { 
                throw std::runtime_error("Erreur inet_pton");
            }
        }

        ~Client() {
            close(sock);
        }

        void send_message_to_server(const char* message) {
            sendto(sock, message, strlen(message), 0, (const struct sockaddr *)&server_addr, sizeof(server_addr));
            socklen_t addrlen = sizeof(server_addr);
            recvfrom(sock, buffer, buffer_size, 0, (struct sockaddr *)&server_addr, &addrlen);
            std::cout << "Message reçu du serveur: " << buffer << std::endl;
        }

    private:
        int sock;
        sockaddr_in server_addr;
        static const size_t buffer_size = 4096;
        char buffer[buffer_size];
};

class Menu {
    public:
        Menu(Client &client) : window(sf::VideoMode(1920, 1080), "Title"), client(client) {
            loadAssets();
            setupSprites();
            menuMusic.play();
        }

        void updateSprites(sf::Vector2i mouse_pos) {
            updateSprite(startGame, 780, 365, mouse_pos, START_GAME);
            updateSprite(options, 780, 460, mouse_pos, OPTIONS);
            updateSprite(exit, 780, 555, mouse_pos, EXIT, true);
        }

        void render() {
            window.clear();
            window.draw(background);
            window.draw(startGame);
            window.draw(options);
            window.draw(exit);
            window.display();
        }

        sf::RenderWindow& getWindow() {
            return window;
        }

    private:
        sf::RenderWindow window;
        Client& client;
        sf::Texture textureBackground, textureStartGame, textureExit, textureOptions;
        sf::Sprite background, startGame, exit, options;
        sf::Music menuMusic;
        enum SpriteId {
            NONE,
            START_GAME,
            OPTIONS,
            EXIT
        };
        SpriteId selectedSprite = NONE;

        void loadAssets() {
            if (!textureStartGame.loadFromFile("../assets/start_game.png") ||
                !textureExit.loadFromFile("../assets/exit.png") ||
                !textureBackground.loadFromFile("../assets/background.png") ||
                !textureOptions.loadFromFile("../assets/options.png") ||
                !menuMusic.openFromFile("../assets/menu_music.ogg")) {
                throw std::runtime_error("Failed to load assets");
            }
        }

        void setupSprites() {
            background.setTexture(textureBackground);
            startGame.setTexture(textureStartGame);
            options.setTexture(textureOptions);
            exit.setTexture(textureExit);
        }

        void updateSprite(sf::Sprite& sprite, float posX, float posY, sf::Vector2i mouse_pos, SpriteId spriteId, bool exitButton = false) {
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
                    if (selectedSprite == START_GAME) {
                        handleStartGame();
                    }
                }
            } else if (selectedSprite == spriteId) {
                selectedSprite = NONE;
            }
        }

        void handleStartGame() {
            client.send_message_to_server("LEFT");
        }
};

int run()
{
    Client client("127.0.0.1", 8000);
    Menu menu(client);
    sf::RenderWindow& window = menu.getWindow();

    while (window.isOpen()) {
        sf::Event event;
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);

        while (window.pollEvent(event)) {
            if (event.key.code == sf::Keyboard::Escape)
                window.close();
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
        return run();
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return -1;
    }
}
