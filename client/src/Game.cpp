/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Game
*/

#include "Game.hpp"
#include <set>

Game::Game()
{
}

Game::~Game()
{
}

SpriteObject Game::createPlayer(int posX, int posY, int id)
{
    SpriteObject ship(m_textureManager.getTexture("player"), sf::Vector2i(33, 17), 5, 10, id);
    int top = (id - 1) * 17;
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

SpriteObject Game::createParallax(int posX, int posY)
{
    SpriteObject parallax(m_textureManager.getTexture("parallax"), sf::Vector2i(1920, 1080), 1, 0, 0);
    parallax.setPosition(posX, posY);
    parallax.sprite.setScale(sf::Vector2f(1.1, 1.1));
    parallax.sprite.setTextureRect(sf::IntRect(0, 0, 1920, 1080));
    return parallax;
}

SpriteObject Game::createBasicSbire(int posX, int posY, int id)
{
    SpriteObject basic_sbire(m_textureManager.getTexture("basic_sbire"), sf::Vector2i(65, 50), 3, 8, id);
    basic_sbire.setPosition(posX, posY);
    basic_sbire.sprite.setScale(sf::Vector2f(2, 2));
    basic_sbire.sprite.setTextureRect(sf::IntRect(0, 0, 65, 50));
    return basic_sbire;
}

SpriteObject Game::createKamikaze(int posX, int posY, int id)
{
    SpriteObject kamikaze(m_textureManager.getTexture("kamikaze"), sf::Vector2i(35, 25), 4, 8, id);
    kamikaze.setPosition(posX, posY);
    kamikaze.sprite.setScale(sf::Vector2f(2, 2));
    kamikaze.sprite.setTextureRect(sf::IntRect(0, 0, 33, 32));
    return kamikaze;
}

void Game::parseBuffer(const std::string& buffer)
{
    std::istringstream stream(buffer);
    std::string line;
    std::set<int> currentIds;

    while (std::getline(stream, line)) {
        if (line.rfind("Entity", 0) == 0) {
            EntityData data;
            std::sscanf(line.c_str(), "Entity %d position: (%f, %f) HP: %d", &data.id, &data.position.x, &data.position.y, &data.hp);

            currentIds.insert(data.id);

            auto it = std::find_if(m_object.begin(), m_object.end(), [&data](const SpriteObject &obj) {
                return obj.getId() == data.id;
            });

            if (it != m_object.end()) {
                it->setPosition(data.position.x, data.position.y);
            } else {
                if (data.id >= 1 && data.id <= 4) {
                    SpriteObject newObject = createPlayer(data.position.x, data.position.y, data.id);
                    m_object.push_back(newObject);
                } else if (data.id >= 5 && data.id < 200) {
                    SpriteObject newObject = createSbire(data.position.x, data.position.y, data.id);
                    m_object.push_back(newObject);
                } else if (data.id >= 200 && data.id < 500) {
                    SpriteObject newObject = createBullet(data.position.x, data.position.y, data.id);
                    m_object.push_back(newObject);
                }
                else if (data.id >= 500 && data.id < 1000) {
                    SpriteObject newObject = createKamikaze(data.position.x, data.position.y, data.id);
                    m_object.push_back(newObject);
                }
            }
        }
        if (line.rfind("DEAD", 0) == 0) {
            m_game_is_over = true;
            std::cout << "Player DEAD" << std::endl;
        }
    }

    auto it = std::remove_if(m_object.begin(), m_object.end(), [&currentIds](const SpriteObject& obj) {
        return currentIds.find(obj.getId()) == currentIds.end();
    });

    m_object.erase(it, m_object.end());
}

void Game::run(sf::RenderWindow &window, std::string buffer, sf::Time deltaTime, SpriteObject m_parallax)
{
    parseBuffer(buffer);
    m_parallax.draw(window);

    for (auto& element: m_object) {
        element.update(deltaTime);
        element.draw(window);
    }
}
