#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

class Menu {
public:
    Menu() : window(sf::VideoMode(1920, 1080), "Title") {
        loadAssets();
        setupSprites();
        menuMusic.play();
    }

    void updateSprites(sf::Vector2i mouse_pos) {
        updateSprite(startGame, 780, 365, mouse_pos);
        updateSprite(options, 780, 460, mouse_pos);
        updateSprite(exit, 780, 555, mouse_pos, true);
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
    sf::Texture textureBackground, textureStartGame, textureExit, textureOptions;
    sf::Sprite background, startGame, exit, options;
    sf::Music menuMusic;

    void loadAssets() {
        if (!textureStartGame.loadFromFile("../../assets/start_game.png") ||
            !textureExit.loadFromFile("../../assets/exit.png") ||
            !textureBackground.loadFromFile("../../assets/background.png") ||
            !textureOptions.loadFromFile("../../assets/options.png") ||
            !menuMusic.openFromFile("../../assets/menu_music.ogg")) {
            throw std::runtime_error("Failed to load assets");
        }
    }

    void setupSprites() {
        background.setTexture(textureBackground);
        startGame.setTexture(textureStartGame);
        options.setTexture(textureOptions);
        exit.setTexture(textureExit);
    }

    void updateSprite(sf::Sprite& sprite, float posX, float posY, sf::Vector2i mouse_pos, bool exitButton = false) {
        sprite.setScale(1.10, 1.10);
        sprite.setPosition(posX, posY);
        if (sprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos))) {
            sprite.setScale(1.15, 1.15);
            sprite.setPosition(posX - 5, posY);
            if (exitButton && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                window.close();
            }
        }
    }
};

int run()
{
    Menu menu;
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
        return run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
}
