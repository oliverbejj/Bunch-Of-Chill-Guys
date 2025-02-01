#include "Bullet.hpp"

Bullet::Bullet(float x, float y, float dirX, float dirY) {
    shape.setRadius(5);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(x, y);
    velocity = sf::Vector2f(dirX, dirY);
}

void Bullet::update() {
    shape.move(velocity * speed);
}

void Bullet::draw(sf::RenderWindow &window) {
    window.draw(shape);
}

sf::FloatRect Bullet::getBounds() {
    return shape.getGlobalBounds();
}
