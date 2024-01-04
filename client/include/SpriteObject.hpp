/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** SpriteObject
*/

#ifndef SPRITEOBJECT_HPP_
#define SPRITEOBJECT_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>

class SpriteObject {
    public:
        SpriteObject() = default;
        SpriteObject(const sf::Texture& texture, sf::Vector2i frameSize, int frameCount, int frameDelay, int id)
        : sprite(texture), frameSize(frameSize), m_id(id), frameCount(frameCount), frameDelay(frameDelay), currentFrame(0), elapsedTime(0) {
            updateFrame(m_id);
        }

        ~SpriteObject() {}  // Destructeur virtuel

        void update(sf::Time deltaTime) {
            elapsedTime += deltaTime.asMilliseconds();

            if (elapsedTime >= frameDelay) {
                elapsedTime = 0;
                currentFrame = (currentFrame + 1) % frameCount;
                updateFrame(m_id);
            }
        }

        void moveHorizontally(float offset) { // Fonction pour déplacer le parallax
            sf::Vector2f position = sprite.getPosition();
            position.x += offset;
            sprite.setPosition(position);
        }

        void draw(sf::RenderWindow& window) {
            window.draw(sprite);
        }

        void setPosition(float x, float y) {
            sprite.setPosition(x, y);
        }

        void setTexture(const sf::Texture& texture) {
            sprite.setTexture(texture);
        }
        int getId() const { return m_id; }

        sf::Sprite sprite;

    protected:
        sf::Vector2i frameSize;
        int m_id;
        int frameCount;
        int frameDelay;
        int currentFrame;
        int elapsedTime;
        bool m_toShow = true;

        void updateFrame(int id) {
            int frameX = frameSize.x * (currentFrame % frameCount);
            int frameY = frameSize.y * (currentFrame / frameCount);
            if (id == 2)
                frameY = 17;
            if (id == 3)
                frameY = 34;
            if (id == 4)
                frameY = 51;
            sprite.setTextureRect(sf::IntRect(frameX, frameY, frameSize.x, frameSize.y));
        }
};

#endif // SPRITEOBJECT_HPP_

