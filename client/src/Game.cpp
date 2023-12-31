/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Game
*/

#include "Game.hpp"

Game::Game()
{
}

Game::~Game()
{
}

SpriteObject Game::createPlayer(int posX, int posY, int id)
{
    SpriteObject ship(m_textureManager.getTexture("player"), sf::Vector2i(33, 17), 5, 10, id);
    int top = (id - 1) * 17; // Calculate the top coordinate based on the ID
    int left = 0;

    ship.setPosition(posX, posY);
    ship.sprite.setScale(sf::Vector2f(2, 2));
    ship.sprite.setTextureRect(sf::IntRect(top, left, 33, 17));
    sf::FloatRect bounds = ship.sprite.getLocalBounds();
    ship.sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);

    return ship;
}


SpriteObject Game::createBullet(int posX, int posY, int id)
{
    SpriteObject bullet(m_textureManager.getTexture("bullet"), sf::Vector2i(17, 18), 12, 4, id);
    bullet.setPosition(posX, posY);
    // bullet.sprite.setScale(sf::Vector2f(2, 2));
    bullet.sprite.setTextureRect(sf::IntRect(0, 0, 17, 18));
    sf::FloatRect bounds = bullet.sprite.getLocalBounds();
    bullet.sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    return bullet;
}

SpriteObject Game::createSbire(int posX, int posY, int id)
{
    SpriteObject sbire(m_textureManager.getTexture("sbire"), sf::Vector2i(33, 34), 3, 15, id);
    sbire.setPosition(posX, posY);
    sbire.sprite.setScale(sf::Vector2f(2, 2));
    sbire.sprite.setTextureRect(sf::IntRect(0, 0, 33, 34));
    sf::FloatRect bounds = sbire.sprite.getLocalBounds();
    sbire.sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    return sbire;
}

SpriteObject Game::createBasicSbire(int posX, int posY, int id)
{
    SpriteObject basic_sbire(m_textureManager.getTexture("basic_sbire"), sf::Vector2i(65, 50), 3, 8, id);
    basic_sbire.setPosition(posX, posY);
    basic_sbire.sprite.setScale(sf::Vector2f(2, 2));
    basic_sbire.sprite.setTextureRect(sf::IntRect(0, 0, 65, 50));
    return basic_sbire;
}

void Game::parseBuffer(const std::string& buffer)
{
    std::istringstream stream(buffer);
    std::string line;

    while (std::getline(stream, line)) {
        if (line.rfind("Entity", 0) == 0) {
            EntityData data;
            std::sscanf(line.c_str(), "Entity %d position: (%f, %f) HP: %d", &data.id, &data.position.x, &data.position.y, &data.hp);

            auto it = std::find_if(m_object.begin(), m_object.end(), [&data](const SpriteObject& obj) {
                return obj.getId() == data.id; // Assurez-vous que SpriteObject a une méthode getId()
            });

            if (it != m_object.end()) {
                // Si l'entité existe, mettez à jour sa position
                it->setPosition(data.position.x, data.position.y);
            } else {
                if (data.id >= 1 && data.id <= 4) { // Joueur
                    SpriteObject newObject = createPlayer(data.position.x, data.position.y, data.id);
                    m_object.push_back(newObject);
                } else if (data.id >= 5 && data.id <= 200) { // Monstre
                    SpriteObject newObject = createSbire(data.position.x, data.position.y, data.id);
                    m_object.push_back(newObject);
                } else if (data.id >= 201 && data.id <= 500) { // Missile
                    SpriteObject newObject = createBullet(data.position.x, data.position.y, data.id);
                    m_object.push_back(newObject);
                }
            }
        }
    }
}

void Game::run(sf::RenderWindow& window, std::string buffer, sf::Time deltaTime)
{
    parseBuffer(buffer);

    for (auto& element: m_object) {
        element.update(deltaTime);
        element.draw(window);
    }
}
