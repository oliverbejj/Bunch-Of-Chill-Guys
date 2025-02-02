#include "Bullet.hpp"

Bullet::Bullet(float x, float y, float dirX, float dirY) {
    shape.setSize(sf::Vector2f(10, 5));
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(x, y);
    direction = sf::Vector2f(dirX, dirY);
    speed = 5.0f;
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
