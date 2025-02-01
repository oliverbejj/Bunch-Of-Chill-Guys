#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

class Player {
public:
    Player(float x, float y, sf::Color color);
    void update(sf::Keyboard::Key up, sf::Keyboard::Key down, sf::Keyboard::Key left, sf::Keyboard::Key right);
    void draw(sf::RenderWindow& window);
    sf::Vector2f getPosition();
    sf::Vector2f getSize();               // Added
    void setPosition(float x, float y);   // Added

private:
    sf::RectangleShape shape;
    float speed = 4.0f;
};

#endif
