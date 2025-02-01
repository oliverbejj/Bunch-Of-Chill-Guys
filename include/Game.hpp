#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.hpp"
#include "Bullet.hpp"
#include "Menu.hpp" 

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();
    void handleShooting();
    void handleResize(int windowWidth, int windowHeight);
    void handleMenuInput(sf::Event event);  // Add this
    void handleGameInput(sf::Event event);
    void restartGame();

    sf::RenderWindow window;
    sf::View view;
    sf::RectangleShape menuButton;    // Button to open the menu
    sf::Text menuButtonText;  
    Player player1, player2;
    std::vector<Bullet> bullets;

    // For displaying controls
    sf::Font font;
    sf::Text controlsText;
    Menu menu;         // Add the menu
    bool inMenu = true;
};

#endif
