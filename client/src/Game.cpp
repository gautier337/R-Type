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

SpriteObject Game::createPlayer(int posX, int posY)
{
    SpriteObject ship(m_textureManager.getTexture("player"), sf::Vector2i(33, 17), 5, 10);

    ship.setPosition(posX, posY);
    ship.sprite.setScale(sf::Vector2f(2, 2));
    ship.sprite.setTextureRect(sf::IntRect(0, 0, 33, 17));

    return ship;
}

SpriteObject Game::createBullet(int posX, int posY)
{
    SpriteObject bullet(m_textureManager.getTexture("bullet"), sf::Vector2i(17, 18), 12, 4);
    bullet.setPosition(posX, posY);
    // bullet.sprite.setScale(sf::Vector2f(2, 2));
    bullet.sprite.setTextureRect(sf::IntRect(0, 0, 17, 18));
    return bullet;
}

SpriteObject Game::createSbire(int posX, int posY)
{
    SpriteObject sbire(m_textureManager.getTexture("sbire"), sf::Vector2i(33, 34), 3, 15);
    sbire.setPosition(posX, posY);
    sbire.sprite.setScale(sf::Vector2f(2, 2));
    sbire.sprite.setTextureRect(sf::IntRect(0, 0, 33, 34));
    return sbire;
}

SpriteObject Game::createBasicSbire(int posX, int posY)
{
    SpriteObject basic_sbire(m_textureManager.getTexture("basic_sbire"), sf::Vector2i(65, 50), 3, 8);
    basic_sbire.setPosition(posX, posY);
    basic_sbire.sprite.setScale(sf::Vector2f(2, 2));
    basic_sbire.sprite.setTextureRect(sf::IntRect(0, 0, 65, 50));
    return basic_sbire;

}

void Game::run(sf::RenderWindow& window, std::string buffer, sf::Time deltaTime)
{
    for (auto& element: m_object) {
        element.update(deltaTime);
        element.draw(window);
    }
}
void Game::LoadAllTexture()
{

}