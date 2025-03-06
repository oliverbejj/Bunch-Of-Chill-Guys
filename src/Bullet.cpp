#include "Bullet.hpp"
#include <cmath>

Bullet::Bullet(float x, float y, float dirX, float dirY) {
    shape.setSize(sf::Vector2f(10, 5));
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(x, y);

    //  Normalize direction for consistent speed
    float magnitude = std::sqrt(dirX * dirX + dirY * dirY);
    direction = (magnitude != 0) ? sf::Vector2f(dirX / magnitude, dirY / magnitude) : sf::Vector2f(1, 0);
    
    speed = 10.0f;  // Bullet speed
}

void Bullet::update() {
    shape.move(direction * speed);
}



void Bullet::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::FloatRect Bullet::getBounds() const {
    return shape.getGlobalBounds();
}
