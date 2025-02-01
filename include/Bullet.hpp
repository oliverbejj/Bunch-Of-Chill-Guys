#ifndef BULLET_HPP
#define BULLET_HPP

#include <SFML/Graphics.hpp>

class Bullet {
public:
    Bullet(float x, float y, float dirX, float dirY);
    void update();
    void draw(sf::RenderWindow &window);
    sf::FloatRect getBounds();

private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float speed = 8.0f;
};

#endif
