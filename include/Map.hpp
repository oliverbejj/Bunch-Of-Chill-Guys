#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Map {
public:
    Map();
    void createMapLayout(int width, int height);
    void resize(int windowWidth, int windowHeight);
    void draw(sf::RenderWindow& window);
    bool checkCollision(const sf::FloatRect& bounds) const;

private:
    std::vector<sf::RectangleShape> walls;
    bool checkRotatedCollision(const sf::RectangleShape& shape, const sf::FloatRect& bounds) const;
    bool checkSATCollision(const sf::Vector2f* rectPoints, const sf::FloatRect& bounds) const;
};

#endif // MAP_HPP
