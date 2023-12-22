/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** SpriteObject
*/

#ifndef SPRITEOBJECT_HPP_
#define SPRITEOBJECT_HPP_

#include <SFML/Graphics.hpp>

class SpriteObject {
    public:
        SpriteObject(const sf::Texture& texture, sf::Vector2i frameSize, int frameCount, int frameDelay)
        : sprite(texture), frameSize(frameSize), frameCount(frameCount), frameDelay(frameDelay), currentFrame(0), elapsedTime(0) {
            updateFrame();
        }

        ~SpriteObject() {}  // Destructeur virtuel

        void update(sf::Time deltaTime) {
            elapsedTime += deltaTime.asMilliseconds();
            if (elapsedTime >= frameDelay) {
                elapsedTime = 0;
                currentFrame = (currentFrame + 1) % frameCount;
                updateFrame();
            }
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

    protected:
        sf::Sprite sprite;
        sf::Vector2i frameSize;
        int frameCount;
        int frameDelay;
        int currentFrame;
        int elapsedTime;

        void updateFrame() {
            int frameX = frameSize.x * (currentFrame % frameCount);
            int frameY = frameSize.y * (currentFrame / frameCount);
            sprite.setTextureRect(sf::IntRect(frameX, frameY, frameSize.x, frameSize.y));
        }
};

#endif // SPRITEOBJECT_HPP_

