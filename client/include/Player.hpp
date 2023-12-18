/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Player
*/

#pragma once

#include <SFML/Graphics.hpp>

class Player {
public:
    Player(float x, float y, float speed);
    void update();
    void draw(sf::RenderWindow &window);

    void setVelocityX(float x);
    void setVelocityY(float y);
    void resetVelocity();
    float getSpeed() const;
    void accumulateVelocity(float x, float y);

private:
    sf::RectangleShape shape;
    float speed;
    sf::Vector2f velocity;
};
