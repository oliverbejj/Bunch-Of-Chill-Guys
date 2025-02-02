#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "Map.hpp"

class Player {
public:
    Player(float x, float y, sf::Color color);
    void update(sf::Keyboard::Key up, sf::Keyboard::Key down, sf::Keyboard::Key left, sf::Keyboard::Key right,
                const sf::RenderWindow& window, const Map& map);
    void draw(sf::RenderWindow& window);
    sf::Vector2f getPosition();
    sf::Vector2f getSize();
    void setPosition(float x, float y);
    sf::FloatRect getBounds();
    void undoMove();

private:
    sf::RectangleShape shape;
    sf::Vector2f lastMovement;
    float speed;
};

#endif
