#include <SFML/Graphics.hpp>

int menu()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Title");
    sf::Texture texture_background;
    sf::Texture texture_start_game;
    sf::Texture texture_exit;
    sf::Texture texture_options;

    if (!texture_start_game.loadFromFile("../../assets/start_game.png"))
        return -1;
    if (!texture_exit.loadFromFile("../../assets/exit.png"))
        return -1;
    if (!texture_background.loadFromFile("../../assets/background.png"))
        return -1;
    if (!texture_options.loadFromFile("../../assets/options.png"))
        return -1;

    sf::Sprite background;
    sf::Sprite start_game;
    sf::Sprite exit;
    sf::Sprite options;
    background.setTexture(texture_background);
    start_game.setTexture(texture_start_game);
    options.setTexture(texture_options);
    exit.setTexture(texture_exit);

    while (window.isOpen()) {
        sf::Event event;
        sf ::Vector2i mouse_pos = sf::Mouse::getPosition(window);

        while (window.pollEvent(event)) {
            if (event.key.code == sf::Keyboard::Escape)
                window.close();
        }
        start_game.setScale(1.10, 1.10);
        options.setScale(1.10, 1.10);
        exit.setScale(1.10, 1.10);
        start_game.setPosition(780, 365);
        options.setPosition(780, 460);
        exit.setPosition(780, 555);
        if (start_game.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos))) {
            start_game.setScale(1.15, 1.15);
            start_game.setPosition(775, 365);
        }
        if (options.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos))) {
            options.setScale(1.15, 1.15);
            options.setPosition(775, 460);
        }
        if (exit.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos))) {
            exit.setPosition(775, 555);
            exit.setScale(1.15, 1.15);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                window.close();
        }
        window.clear();
        window.draw(background);
        window.draw(start_game);
        window.draw(options);
        window.draw(exit);
        window.display();
    }
    return 0;
}

int main()
{
    menu();
    return 0;
}
