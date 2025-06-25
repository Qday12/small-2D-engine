//
// Created by qday on 6/23/25.
//

#include "ball.h"

Ball::Ball(float radius) {
    this->shape.setRadius(radius);
    this->shape.setOutlineThickness(0);
    this->shape.setFillColor(sf::Color::Red);
    this->shape.setOrigin(sf::Vector2f(radius, radius));
    this->shape.setPosition(position_current);
}

void Ball::updatePosition(float dt) {

    sf::Vector2f velocity = position_current - position_old;

    position_old = position_current;

    position_current = position_current + velocity + acceleration * dt * dt;
    shape.setPosition(position_current);

    acceleration = sf::Vector2f(0, 0);
}

void Ball::accelerate(sf::Vector2f acc) {
    acceleration += acc;
}