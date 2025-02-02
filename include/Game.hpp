#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.hpp"
#include "Bullet.hpp"
#include "Map.hpp"
#include "Menu.hpp"

class Game {
public:
    Game();
    void run();

private:
    // Core game loop
    void processEvents();
    void update();
    void render();

    // Event handling
    void handleMenuInput(sf::Event event);
    void handleShooting();
    void handleResize(int windowWidth, int windowHeight);

    // Utility
    void shoot(Player& player);
    void restartGame();

    // Window & View
    sf::RenderWindow window;
    sf::View view;

    // Game elements
    Player player1, player2;
    std::vector<Bullet> bullets;
    Map map;

    // Menu elements
    Menu menu;
    bool inMenu; // true if we’re showing the menu

    // UI elements
    sf::Font font;
    sf::Text controlsText;

    // “Hamburger” button to open the menu
    sf::RectangleShape menuButton;
    sf::Text menuButtonText;
};

#endif
