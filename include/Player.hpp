#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "Map.hpp"               // ✅ Required for collision handling
#include <iostream>              // ✅ Needed for error logging

class Player {
public:
    Player(float x, float y, sf::Color color, const std::string &textureFile = "assets/soldier/soldier1_gun.png");

    void update(sf::Keyboard::Key up, sf::Keyboard::Key down,
                sf::Keyboard::Key left, sf::Keyboard::Key right,
                const sf::RenderWindow& window, const Map& map, const Player& otherPlayer);  // ✅ Combined update function

    void draw(sf::RenderWindow& window);

    sf::Vector2f getPosition();
    sf::Vector2f getSize();
    void setPosition(float x, float y);
    sf::FloatRect getBounds() const;
    float getRotation();        // ✅ Needed for shooting in the direction of rotation
    void setRotation(float angle);

    void undoMove();            // ✅ For collision response

private:
    sf::RectangleShape shape;   // Player hitbox
    sf::Texture texture;        // Player sprite texture
    sf::Sprite sprite;          // Player sprite for animation
    sf::Vector2f lastMovement;  // For undoing movement after collisions
    float speed = 4.0f;         // Movement speed

    bool checkPlayerCollision(const sf::FloatRect& otherBounds);  // ✅ For player-to-player collision
};

#endif
