#include "Player.hpp"
#include "Map.hpp"
#include <iostream>

Player::Player(float x, float y, sf::Color color, const std::string &textureFile) {
    // Load texture
    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "Error loading texture!" << std::endl;
    }

    sprite.setTexture(texture);
    // Center the sprite based on its own dimensions
    sprite.setOrigin(sprite.getGlobalBounds().width / 2.f, 
                     sprite.getGlobalBounds().height / 2.f);

    // Use a circle shape (50px diameter to match the old 50x50 rectangle)
    shape.setRadius(17.f);
    shape.setFillColor(sf::Color::Transparent); 
    shape.setOrigin(shape.getRadius(), shape.getRadius());
    shape.setPosition(x, y);
}

void Player::update(sf::Keyboard::Key up, 
                    sf::Keyboard::Key down,
                    sf::Keyboard::Key left, 
                    sf::Keyboard::Key right,
                    const sf::RenderWindow& window, 
                    const Map& map,
                    const Player& otherPlayer) 
{
    sf::Vector2f movement(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(up)) {
        movement.y -= speed;
        sprite.setRotation(-90.f);
    }
    if (sf::Keyboard::isKeyPressed(down)) {
        movement.y += speed;
        sprite.setRotation(90.f);
    }
    if (sf::Keyboard::isKeyPressed(left)) {
        movement.x -= speed;
        sprite.setRotation(180.f);
    }
    if (sf::Keyboard::isKeyPressed(right)) {
        movement.x += speed;
        sprite.setRotation(0.f);
    }

    lastMovement = movement;

    // Move horizontally, check collision, revert if collided
    shape.move(movement.x, 0.f);
    if (map.checkCollision(getBounds()) || checkPlayerCollision(otherPlayer.getBounds())) {
        shape.move(-movement.x, 0.f);
    }

    // Move vertically, check collision, revert if collided
    shape.move(0.f, movement.y);
    if (map.checkCollision(getBounds()) || checkPlayerCollision(otherPlayer.getBounds())) {
        shape.move(0.f, -movement.y);
    }

    // Keep Player Within Window Bounds
    sf::Vector2f pos = shape.getPosition();
    sf::Vector2u windowSize = window.getSize();
    float r = shape.getRadius();

    if (pos.x - r < 0)                     shape.setPosition(r, pos.y);
    if (pos.y - r < 0)                     shape.setPosition(pos.x, r);
    if (pos.x + r > windowSize.x)          shape.setPosition(windowSize.x - r, pos.y);
    if (pos.y + r > windowSize.y)          shape.setPosition(pos.x, windowSize.y - r);

    // Sync sprite with shape
    sprite.setPosition(shape.getPosition());
}

bool Player::checkPlayerCollision(const sf::FloatRect& otherBounds) {
    // Using bounding-box intersection for the circle, 
    // but you could refine to real circle collision if desired
    return shape.getGlobalBounds().intersects(otherBounds);
}

void Player::draw(sf::RenderWindow& window) {
    // Draw the circle shape (for debugging or aesthetic)
    window.draw(shape);
    // Draw the sprite
    window.draw(sprite);
}

sf::Vector2f Player::getPosition() {
    return shape.getPosition();
}

// Return diameter as (width, height) for the existing code that calls getSize()
sf::Vector2f Player::getSize() const {
    float diameter = 2.f * shape.getRadius();
    return sf::Vector2f(diameter, diameter);
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
void Player::setShapeColor(const sf::Color& color) {
    shape.setFillColor(color);
    
}

void Player::resetHealth() {
    health = 100;  // Full health
}

