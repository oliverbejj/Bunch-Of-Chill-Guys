#include "Player.hpp"

Player::Player(float x, float y, sf::Color color) {
    shape.setSize(sf::Vector2f(50, 50));
    shape.setFillColor(color);
    shape.setPosition(x, y);
    speed = 3.0f; // Default speed
}

void Player::update(sf::Keyboard::Key up, sf::Keyboard::Key down,
                    sf::Keyboard::Key left, sf::Keyboard::Key right,
                    const sf::RenderWindow& window, const Map& map, const Player& otherPlayer) {
    sf::Vector2f movement(0, 0);

    // ✅ Movement Input
    if (sf::Keyboard::isKeyPressed(up))
        movement.y -= speed;
    if (sf::Keyboard::isKeyPressed(down))
        movement.y += speed;
    if (sf::Keyboard::isKeyPressed(left))
        movement.x -= speed;
    if (sf::Keyboard::isKeyPressed(right))
        movement.x += speed;

    lastMovement = movement;  // Store for undo functionality

    // ✅ Move Horizontally First
    shape.move(movement.x, 0);
    if (map.checkCollision(getBounds()) || checkPlayerCollision(otherPlayer.getBounds())) {
        shape.move(-movement.x, 0);  // Undo horizontal movement if collision detected
    }

    // ✅ Move Vertically
    shape.move(0, movement.y);
    if (map.checkCollision(getBounds()) || checkPlayerCollision(otherPlayer.getBounds())) {
        shape.move(0, -movement.y);  // Undo vertical movement if collision detected
    }

    // ✅ Keep Player Within Window Bounds
    sf::FloatRect bounds = shape.getGlobalBounds();
    if (bounds.left < 0) shape.setPosition(0, shape.getPosition().y);
    if (bounds.top < 0) shape.setPosition(shape.getPosition().x, 0);
    if (bounds.left + bounds.width > window.getSize().x)
        shape.setPosition(window.getSize().x - bounds.width, shape.getPosition().y);
    if (bounds.top + bounds.height > window.getSize().y)
        shape.setPosition(shape.getPosition().x, window.getSize().y - bounds.height);
}


// ✅ Player-to-Player Collision Check
bool Player::checkPlayerCollision(const sf::FloatRect& otherBounds) {
    return shape.getGlobalBounds().intersects(otherBounds);
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

sf::FloatRect Player::getBounds() const {
    return shape.getGlobalBounds();
}


void Player::undoMove() {
    shape.move(-lastMovement);
}
