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
        SpriteObject(const sf::Texture& texture, sf::Vector2i frameSize, int frameCount, int frameDelay)
        : sprite(texture), frameSize(frameSize), frameCount(frameCount), frameDelay(frameDelay), currentFrame(0), elapsedTime(0) {
            updateFrame();
        }

        ~SpriteObject() {}  // Destructeur virtuel

        void update(sf::Time deltaTime) {
            elapsedTime += deltaTime.asMilliseconds();
            std::cout << "Temps écoulé: " << elapsedTime << std::endl; // Message de débogage

            if (elapsedTime >= frameDelay) {
                elapsedTime = 0;
                currentFrame = (currentFrame + 1) % frameCount;
                updateFrame();
                std::cout << "Frame actuelle: " << currentFrame << std::endl; // Message de débogage
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
        sf::Sprite sprite;

    protected:
        sf::Vector2i frameSize;
        int frameCount;
        int frameDelay;
        int currentFrame;
        int elapsedTime;
        bool m_toShow = true;

        void updateFrame() {
            int frameX = frameSize.x * (currentFrame % frameCount);
            int frameY = frameSize.y * (currentFrame / frameCount);
            sprite.setTextureRect(sf::IntRect(frameX, frameY, frameSize.x, frameSize.y));
        }
};

#endif // SPRITEOBJECT_HPP_

