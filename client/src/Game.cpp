/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Game
*/

#include "Game.hpp"
#include <chrono>

Game::Game()
{
    m_data.wave = 1;
}

Game::~Game()
{
}

////////////////////////////////////////////////////////////
//
// Create an instance of SpriteObject for Player
//
// @param posX pos X of the sprite
// @param posY pos Y of the sprite
// @param id Id of the sprite to track it
////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////
//
// Create an instance of SpriteObject for Bullet
//
// @param posX pos X of the sprite
// @param posY pos Y of the sprite
// @param id Id of the sprite to track it
////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////
//
// Create an instance of SpriteObject for Sbire
//
// @param posX pos X of the sprite
// @param posY pos Y of the sprite
// @param id Id of the sprite to track it
////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////
//
// Create an instance of SpriteObject for the Parallax
//
// @param posX pos X of the sprite
// @param posY pos Y of the sprite
////////////////////////////////////////////////////////////
SpriteObject Game::createParallax(std::string fileName, int posX, int posY)
{
    SpriteObject parallax(m_textureManager.getTexture(fileName), sf::Vector2i(1920, 1080), 1, 0, 0);
    parallax.setPosition(posX, posY);
    parallax.sprite.setScale(sf::Vector2f(1.1, 1.1));
    parallax.sprite.setTextureRect(sf::IntRect(0, 0, 1920, 1080));
    return parallax;
}

////////////////////////////////////////////////////////////
//
// Create an instance of SpriteObject for BasicSbire
//
// @param posX pos X of the sprite
// @param posY pos Y of the sprite
// @param id Id of the sprite to track it
////////////////////////////////////////////////////////////
SpriteObject Game::createBasicSbire(int posX, int posY, int id)
{
    SpriteObject basic_sbire(m_textureManager.getTexture("basic_sbire"), sf::Vector2i(65, 50), 3, 8, id);
    basic_sbire.setPosition(posX, posY);
    basic_sbire.sprite.setScale(sf::Vector2f(1, 1));
    basic_sbire.sprite.setTextureRect(sf::IntRect(0, 0, 65, 50));

    sf::FloatRect bounds = basic_sbire.sprite.getLocalBounds();
    basic_sbire.sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    return basic_sbire;
}

////////////////////////////////////////////////////////////
//
// Create an instance of SpriteObject for Kamikaze
//
// @param posX pos X of the sprite
// @param posY pos Y of the sprite
// @param id Id of the sprite to track it
////////////////////////////////////////////////////////////
SpriteObject Game::createKamikaze(int posX, int posY, int id)
{
    SpriteObject kamikaze(m_textureManager.getTexture("kamikaze"), sf::Vector2i(35, 25), 4, 30, id);
    kamikaze.setPosition(posX, posY);
    kamikaze.sprite.setScale(sf::Vector2f(2, 2));
    kamikaze.sprite.setTextureRect(sf::IntRect(0, 0, 35, 25));
    sf::FloatRect bounds = kamikaze.sprite.getLocalBounds();
    kamikaze.sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    return kamikaze;
}

SpriteObject Game::createKamikazeElite(int posX, int posY, int id)
{
    SpriteObject kamikaze(m_textureManager.getTexture("kamikaze_elite"), sf::Vector2i(49, 50), 5, 30, id);
    kamikaze.setPosition(posX, posY);
    kamikaze.sprite.setScale(sf::Vector2f(2, 2));
    kamikaze.sprite.setTextureRect(sf::IntRect(0, 0, 49, 50));
    sf::FloatRect bounds = kamikaze.sprite.getLocalBounds();
    kamikaze.sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    return kamikaze;
}

////////////////////////////////////////////////////////////
//
// Create an instance of SpriteObject for Boss
//
// @param posX pos X of the sprite
// @param posY pos Y of the sprite
// @param id Id of the sprite to track it
////////////////////////////////////////////////////////////
SpriteObject Game::createBoss(int posX, int posY, int id)
{
    SpriteObject boss(m_textureManager.getTexture("boss"), sf::Vector2i(160, 210), 4, 15, id);
    boss.setPosition(posX, posY);
    boss.sprite.setScale(sf::Vector2f(2, 2));
    boss.sprite.setTextureRect(sf::IntRect(0, 0, 160, 210));
    //make the center of the sprite the origin
    sf::FloatRect bounds = boss.sprite.getLocalBounds();
    boss.sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    return boss;
}

////////////////////////////////////////////////////////////
//
// Create an instance of SpriteObject for Asteroid
//
// @param posX pos X of the sprite
// @param posY pos Y of the sprite
// @param id Id of the sprite to track it
////////////////////////////////////////////////////////////
SpriteObject Game::createAsteroid(int posX, int posY, int id)
{
    SpriteObject asteroid(m_textureManager.getTexture("asteroid"), sf::Vector2i(60, 63), 8, 3, id);
    asteroid.setPosition(posX, posY);
    asteroid.sprite.setScale(sf::Vector2f(1, 1));
    asteroid.sprite.setTextureRect(sf::IntRect(0, 0, 60, 63));
    //make the center of the sprite the origin
    sf::FloatRect bounds =asteroid.sprite.getLocalBounds();
    asteroid.sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    return asteroid;
}

////////////////////////////////////////////////////////////
//
// Create an instance of SpriteObject for BoostBonus
//
// @param posX pos X of the sprite
// @param posY pos Y of the sprite
// @param id Id of the sprite to track it
////////////////////////////////////////////////////////////
SpriteObject Game::createBoostPack(int posX, int posY, int id)
{
    SpriteObject boostPack(m_textureManager.getTexture("boostPack"), sf::Vector2i(412, 406), 1, 0, id);
    boostPack.setPosition(posX, posY);
    boostPack.sprite.setScale(sf::Vector2f(0.1, 0.1));
    boostPack.sprite.setTextureRect(sf::IntRect(0, 0, 412, 406));
    //make the center of the sprite the origin
    sf::FloatRect bounds = boostPack.sprite.getLocalBounds();
    boostPack.sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    return boostPack;
}

////////////////////////////////////////////////////////////
//
// Create an instance of SpriteObject for HealthBonus
//
// @param posX pos X of the sprite
// @param posY pos Y of the sprite
// @param id Id of the sprite to track it
////////////////////////////////////////////////////////////
SpriteObject Game::createHealthPack(int posX, int posY, int id)
{
    SpriteObject HealthPack(m_textureManager.getTexture("healthPack"), sf::Vector2i(436, 429), 1, 0, id);
    HealthPack.setPosition(posX, posY);
    HealthPack.sprite.setScale(sf::Vector2f(0.1, 0.1));
    HealthPack.sprite.setTextureRect(sf::IntRect(0, 0, 436, 429));
    //make the center of the sprite the origin
    sf::FloatRect bounds = HealthPack.sprite.getLocalBounds();
    HealthPack.sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    return HealthPack;
}

////////////////////////////////////////////////////////////
//
// Create an instance of SpriteObject for ShieldBonus
//
// @param posX pos X of the sprite
// @param posY pos Y of the sprite
// @param id Id of the sprite to track it
////////////////////////////////////////////////////////////
SpriteObject Game::createShieldPack(int posX, int posY, int id)
{
    SpriteObject shieldPack(m_textureManager.getTexture("shieldPack"), sf::Vector2i(681, 681), 1, 0, id);
    shieldPack.setPosition(posX, posY);
    shieldPack.sprite.setScale(sf::Vector2f(0.06, 0.06));
    shieldPack.sprite.setTextureRect(sf::IntRect(0, 0, 681, 681));
    //make the center of the sprite the origin
    sf::FloatRect bounds = shieldPack.sprite.getLocalBounds();
    shieldPack.sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    return shieldPack;
}

////////////////////////////////////////////////////////////
//
// Create an instance of SpriteObject for ShieldBonus
//
// @param posX pos X of the sprite
// @param posY pos Y of the sprite
// @param id Id of the sprite to track it
////////////////////////////////////////////////////////////
SpriteObject Game::createShieldField(int posX, int posY, int id)
{
    SpriteObject shieldPack(m_textureManager.getTexture("shieldField"), sf::Vector2i(24, 47), 1, 0, id);
    shieldPack.setPosition(posX, posY);
    shieldPack.sprite.setScale(sf::Vector2f(1, 1));
    shieldPack.sprite.setTextureRect(sf::IntRect(0, 0, 24, 47));
    //make the center of the sprite the origin
    sf::FloatRect bounds = shieldPack.sprite.getLocalBounds();
    shieldPack.sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    return shieldPack;
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
                    m_object.push_back(createPlayer(data.position.x, data.position.y, data.id));
                } else if (data.id >= 5 && data.id < 100) {
                    m_object.push_back(createSbire(data.position.x, data.position.y, data.id));
                } else if (data.id >= 100 && data.id < 200) {
                    m_object.push_back(createBasicSbire(data.position.x, data.position.y, data.id));
                } else if (data.id >= 200 && data.id < 500) {
                    m_object.push_back(createBullet(data.position.x, data.position.y, data.id));
                }
                else if (data.id >= 500 && data.id < 550) {
                    m_object.push_back(createKamikaze(data.position.x, data.position.y, data.id));
                } else if (data.id >= 550 && data.id < 600) {
                    m_object.push_back(createKamikazeElite(data.position.x, data.position.y, data.id));
                } else if (data.id >= 600 && data.id <= 601) {
                    m_object.push_back(createBoss(data.position.x, data.position.y, data.id));
                } else if (data.id >= 603 && data.id < 650) {
                    m_object.push_back(createAsteroid(data.position.x, data.position.y, data.id));
                } else if (data.id == 650) {
                    m_object.push_back(createAsteroid(data.position.x, data.position.y, data.id)); // TETE SERPENT BOSS
                } else if (data.id >= 651 && data.id < 700) {
                    m_object.push_back(createAsteroid(data.position.x, data.position.y, data.id)); // CORPS SERPENT BOSS
                } else if (data.id >= 700 && data.id < 710) {
                    m_object.push_back(createHealthPack(data.position.x, data.position.y, data.id));
                } else if (data.id >= 710 && data.id < 720) {
                    m_object.push_back(createBoostPack(data.position.x, data.position.y, data.id));
                } else if (data.id >= 720 && data.id < 730) {
                    m_object.push_back(createShieldPack(data.position.x, data.position.y, data.id));
                } else if (data.id >= 801 && data.id <= 804) {
                    m_object.push_back(createShieldField(data.position.x, data.position.y, data.id));
                }
            }
            if (data.id >= 1 && data.id <= 4) {
                player_hp = data.hp;
            }
        }
        if (line.rfind("DEAD", 0) == 0) {
            m_game_is_over = true;
        }
        if (line.rfind("Score :", 0) == 0) {
            std::sscanf(line.c_str(), "Score : %d", &m_data.score);
        }
        std::string prefix = "Wave ";
        size_t prefixLength = prefix.length();
        if (line.rfind(prefix, 0) == 0) {
            std::string numberStr = line.substr(prefixLength);
            std::stringstream ss(numberStr);
            int waveNumber;
            if (ss >> waveNumber) {
                m_data.wave = waveNumber;
            } else {
                std::cerr << "Invalid wave number format" << std::endl;
            }
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
    // m_parallax.setPosition(0, 0);

    for (auto& element: m_object) {
        element.update(deltaTime);
        element.draw(window);
    }
}
