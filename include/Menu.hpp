#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Menu {
public:
    Menu(float width, float height);
    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getSelectedItemIndex();
    int getItemIndexAtPosition(sf::Vector2f position);  
    void adjustMenuPositions(float width, float height);
    void showRestartOption(bool show, float width, float height);
    void onHover(sf::Vector2f mousePos);
    sf::Sprite getBackground();  



private:
    sf::Texture backgroundTexture;    // Background texture
    sf::Sprite backgroundSprite; 
    size_t selectedItemIndex;  // Change from int to size_t
    bool showRestart = false;    
    sf::Font font;
    std::vector<sf::Text> menuItems;
};

#endif
