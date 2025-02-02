#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <algorithm>  // For std::max

class Map;  // Forward declaration

class Player {
private:
    // Use a circle instead of a rectangle
    sf::CircleShape shape;
    sf::Sprite sprite;
    sf::Texture texture;

    sf::Vector2f lastMovement;
    float speed = 5.0f;
    int health = 100;  // ✅ Initial health

public:
    // Keep the constructor signature from the newer version
    Player(float x, float y, sf::Color color, const std::string &textureFile);

    // Keep the updated method signature that includes Map & otherPlayer
    void update(sf::Keyboard::Key up, 
                sf::Keyboard::Key down,
                sf::Keyboard::Key left, 
                sf::Keyboard::Key right,
                const sf::RenderWindow& window, 
                const Map& map, 
                const Player& otherPlayer);
    void setShapeColor(const sf::Color& color);  // Add this method declaration


    void draw(sf::RenderWindow& window);

    sf::Vector2f getPosition();
    sf::Vector2f getSize() const;    // We'll return the diameter as Vector2f
    sf::FloatRect getBounds() const;
    float getRotation();
    void setRotation(float angleDegrees);
    void setPosition(float x, float y);
    void undoMove();

    // ✅ Health System
    int getHealth() const { return health; }
    void takeDamage(int damage) { health = std::max(0, health - damage); }
    bool isDead() const { return health <= 0; }
    
    void resetHealth();


private:
    bool checkPlayerCollision(const sf::FloatRect& otherBounds);
};



#endif // PLAYER_HPP
