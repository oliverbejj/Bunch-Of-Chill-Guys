#include "Player.hpp"
#include "Map.hpp"  // ✅ Add this line
#include <iostream>

Player::Player(float x, float y, sf::Color color, const std::string &textureFile) {
    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "Error loading texture!" << std::endl;
    }

    sprite.setTexture(texture);
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);

    shape.setSize(sf::Vector2f(50.0f, 50.0f));
    shape.setFillColor(sf::Color::Transparent);
    shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
    shape.setPosition(x, y);
}

void Player::update(sf::Keyboard::Key up, sf::Keyboard::Key down,
                    sf::Keyboard::Key left, sf::Keyboard::Key right,
                    const sf::RenderWindow& window, const Map& map, const Player& otherPlayer) {
    sf::Vector2f movement(0, 0);

    if (sf::Keyboard::isKeyPressed(up)) {
        movement.y -= speed;
        sprite.setRotation(-90);
    }
    if (sf::Keyboard::isKeyPressed(down)) {
        movement.y += speed;
        sprite.setRotation(90);
    }
    if (sf::Keyboard::isKeyPressed(left)) {
        movement.x -= speed;
        sprite.setRotation(180);
    }
    if (sf::Keyboard::isKeyPressed(right)) {
        movement.x += speed;
        sprite.setRotation(0);
    }

    lastMovement = movement;

    // ✅ Collision Handling
    shape.move(movement.x, 0);
    if (map.checkCollision(getBounds()) || checkPlayerCollision(otherPlayer.getBounds())) {
        shape.move(-movement.x, 0);
    }

    shape.move(0, movement.y);
    if (map.checkCollision(getBounds()) || checkPlayerCollision(otherPlayer.getBounds())) {
        shape.move(0, -movement.y);
    }

    // ✅ Keep Player Within Window Bounds
    sf::Vector2f pos = shape.getPosition();
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2f size = shape.getSize();

    if (pos.x < 0) shape.setPosition(0, pos.y);
    if (pos.y < 0) shape.setPosition(pos.x, 0);
    if (pos.x + size.x > windowSize.x) shape.setPosition(windowSize.x - size.x, pos.y);
    if (pos.y + size.y > windowSize.y) shape.setPosition(pos.x, windowSize.y - size.y);

    // ✅ Sync Sprite with Shape
    sprite.setPosition(shape.getPosition());
}

bool Player::checkPlayerCollision(const sf::FloatRect& otherBounds) {
    return shape.getGlobalBounds().intersects(otherBounds);
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(sprite);
}

sf::Vector2f Player::getPosition() {
    return shape.getPosition();
}

sf::Vector2f Player::getSize() {
    return shape.getSize();
}

sf::FloatRect Player::getBounds() const {
    return shape.getGlobalBounds();
}

float Player::getRotation() {
    return sprite.getRotation();
}

void Player::setRotation(float angleDegrees) {
    sprite.setRotation(angleDegrees);
}

void Player::setPosition(float x, float y) {
    shape.setPosition(x, y);
    sprite.setPosition(x, y);
}

void Player::undoMove() {
    shape.move(-lastMovement);
    sprite.move(-lastMovement);
}
