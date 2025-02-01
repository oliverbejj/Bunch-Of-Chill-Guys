#include "Player.hpp"

Player::Player(float x, float y, sf::Color color) {
    shape.setSize(sf::Vector2f(50, 50));   // Perfect square: 50x50
    shape.setFillColor(color);
    shape.setPosition(x, y);
}

void Player::update(sf::Keyboard::Key up, sf::Keyboard::Key down, sf::Keyboard::Key left, sf::Keyboard::Key right) {
    sf::Vector2f movement(0, 0);

    if (sf::Keyboard::isKeyPressed(up))
        movement.y -= speed;
    if (sf::Keyboard::isKeyPressed(down))
        movement.y += speed;
    if (sf::Keyboard::isKeyPressed(left))
        movement.x -= speed;
    if (sf::Keyboard::isKeyPressed(right))
        movement.x += speed;

    shape.move(movement);

    // Prevent moving outside the window boundaries
    sf::Vector2f pos = shape.getPosition();
    if (pos.x < 0) shape.setPosition(0, pos.y);
    if (pos.y < 0) shape.setPosition(pos.x, 0);
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::Vector2f Player::getPosition() {
    return shape.getPosition();
}

sf::Vector2f Player::getSize() {
    return shape.getSize();
}

void Player::setPosition(float x, float y) {
    shape.setPosition(x, y);
}
