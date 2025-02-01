#include "Player.hpp"
#include <iostream>  // For std::cerr

Player::Player(float x, float y, sf::Color color, const std::string& textureFile)
    : texture(), sprite() 
{
    // Set up the rectangle shape
    shape.setSize(sf::Vector2f(50.0f, 50.0f));  // Example size, adjust as needed
    shape.setFillColor(color);
    shape.setPosition(x, y);

    // Load the texture and set the sprite
    if (!texture.loadFromFile(textureFile)) {
        // Handle the error if the texture is not loaded properly
        std::cerr << "Error loading texture!" << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);  // Optionally set origin to center for better alignment
    sprite.setPosition(x, y);  // Position the sprite over the player
}

void Player::update(sf::Keyboard::Key up, sf::Keyboard::Key down, sf::Keyboard::Key left, sf::Keyboard::Key right, const sf::RenderWindow& window) {
    // Handle player movement here, just like in your existing `update` function
    if (sf::Keyboard::isKeyPressed(up)) {
        shape.move(0, -speed);
    }
    if (sf::Keyboard::isKeyPressed(down)) {
        shape.move(0, speed);
    }
    if (sf::Keyboard::isKeyPressed(left)) {
        shape.move(-speed, 0);
    }
    if (sf::Keyboard::isKeyPressed(right)) {
        shape.move(speed, 0);
    }

    // Update the sprite position to match the shape
    sprite.setPosition(shape.getPosition());
    // Get the current window size for fullscreen boundaries
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2f pos = shape.getPosition();
    sf::Vector2f size = shape.getSize();

    // Ensure boundary conditions for fullscreen
    if (pos.x < 0) shape.setPosition(0, pos.y);                                      // Left boundary
    if (pos.y < 0) shape.setPosition(pos.x, 0);                                      // Top boundary
    if (pos.x + size.x > windowSize.x) shape.setPosition(windowSize.x - size.x, pos.y); // Right boundary
    if (pos.y + size.y > windowSize.y) shape.setPosition(pos.x, windowSize.y - size.y); // Bottom boundary
}

void Player::draw(sf::RenderWindow& window) {
    // Draw the player shape
    window.draw(shape);
    
    // Draw the sprite (image) on top of the player
    window.draw(sprite);
}

sf::Vector2f Player::getPosition() {
    return shape.getPosition();
}

sf::Vector2f Player::getSize() {
    return shape.getSize();
}

void Player::setPosition(float x, float y) {
    shape.setPosition(x, y);
    sprite.setPosition(x, y);  // Set the sprite position as well
}
