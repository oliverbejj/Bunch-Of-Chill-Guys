#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <algorithm>  // For std::max

class Map;  // Forward declaration

class Player {
private:
    sf::RectangleShape shape;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f lastMovement;
    float speed = 5.0f;
    int health = 100;  // ✅ Initial health

public:
    Player(float x, float y, sf::Color color, const std::string &textureFile);
    void update(sf::Keyboard::Key up, sf::Keyboard::Key down, sf::Keyboard::Key left, sf::Keyboard::Key right,
                const sf::RenderWindow& window, const Map& map, const Player& otherPlayer);
    void draw(sf::RenderWindow& window);
    sf::Vector2f getPosition();
    sf::Vector2f getSize();
    sf::FloatRect getBounds() const;
    float getRotation();
    void setRotation(float angleDegrees);
    void setPosition(float x, float y);
    void undoMove();

    // ✅ Health System Methods
    int getHealth() const { return health; }
    void takeDamage(int damage) { health = std::max(0, health - damage); }
    bool isDead() const { return health <= 0; }

private:
    bool checkPlayerCollision(const sf::FloatRect& otherBounds);
};

#endif // PLAYER_HPP
