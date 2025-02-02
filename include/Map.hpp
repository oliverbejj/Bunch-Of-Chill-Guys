#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Map {
public:
    Map();
    void draw(sf::RenderWindow& window);
    bool checkCollision(const sf::FloatRect& bounds) const;
    void resize(int width, int height);  // Adjust for fullscreen
    bool checkRotatedCollision(const sf::RectangleShape& shape, const sf::FloatRect& bounds) const;
    bool checkSATCollision(const sf::Vector2f* rectPoints, const sf::FloatRect& bounds) const;



private:
    std::vector<sf::RectangleShape> walls;
    void createMapLayout(int width, int height);  // Custom map layout
};

#endif
