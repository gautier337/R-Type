#include <SFML/Graphics.hpp>

int menu()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Title");
    sf::Texture texture_background;
    sf::Texture texture_start_game;
    sf::Texture texture_exit;
    sf::Texture texture_options;
    int screen_width = window.getSize().x;
    int screen_height = window.getSize().y;

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
    sf::Sprite tmp;
    background.setTexture(texture_background);
    start_game.setTexture(texture_start_game);
    options.setTexture(texture_options);
    exit.setTexture(texture_exit);
    tmp.setTexture(texture_options);

    while (window.isOpen()) {
        sf::Event event;
        sf ::Vector2i mouse_pos = sf::Mouse::getPosition(window);

        while (window.pollEvent(event)) {
            if (event.key.code == sf::Keyboard::Escape)
                window.close();
        }
        background.setPosition(0, 0);
        start_game.setScale(0.95, 0.95);
        options.setScale(0.95, 0.95);
        exit.setScale(0.95, 0.95);
        tmp.setScale(0.95, 0.95);
        background.setScale(
            float(screen_width) / float(texture_background.getSize().x),
            float(screen_height) / float(texture_background.getSize().y));
        start_game.setPosition(screen_width / 2, screen_height / 2 - 95);
        tmp.setPosition(screen_width / 2, screen_height / 2 - 20);
        options.setPosition(screen_width / 2, screen_height / 2 + 55);
        exit.setPosition(screen_width / 2, screen_height / 2 + 130);
        start_game.setOrigin(
            start_game.getGlobalBounds().width / 2,
            start_game.getGlobalBounds().height / 2);
        options.setOrigin(
            options.getGlobalBounds().width / 2,
            options.getGlobalBounds().height / 2);
        exit.setOrigin(
            exit.getGlobalBounds().width / 2,
            exit.getGlobalBounds().height / 2);
        tmp.setOrigin(
            tmp.getGlobalBounds().width / 2,
            tmp.getGlobalBounds().height / 2);

        if (start_game.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos)))
            start_game.setScale(1.00, 1.00);
        if (options.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos)))
            options.setScale(1.00, 1.00);
        if (exit.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos))) {
            exit.setScale(1.00, 1.00);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                window.close();
        }
        if (tmp.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos)))
            tmp.setScale(1.00, 1.00);
        window.clear();
        window.draw(background);
        window.draw(start_game);
        window.draw(options);
        window.draw(exit);
        window.draw(tmp);
        window.display();
    }
    return 0;
}

int main()
{
    menu();
    return 0;
}
