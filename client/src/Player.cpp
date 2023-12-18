/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Player
*/

#include "../include/Player.hpp"

Player::Player(float x, float y, float speed) : speed(speed), velocity(0, 0) {
    shape.setSize(sf::Vector2f(30, 30));
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::White);
}

void Player::setVelocityX(float x) {
    velocity.x = x;
}

void Player::setVelocityY(float y) {
    velocity.y = y;
}

void Player::resetVelocity() {
    velocity.x = 0.0f;
    velocity.y = 0.0f;
}

float Player::getSpeed() const {
    return speed;
}

void Player::update() {
    shape.move(velocity);
}

void Player::draw(sf::RenderWindow &window) {
    window.draw(shape);
}

void Player::accumulateVelocity(float x, float y) {
    velocity.x += x;
    velocity.y += y;
}
