#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.hpp"
#include "Bullet.hpp"
#include "Map.hpp"  // ✅ For collision handling

class Game {
public:
    Game();
    void run();

private:
    // ✅ Core Game Loop Functions
    void processEvents();
    void update();
    void render();
    void handleShooting();                  // ✅ Handles shooting logic
    void handleResize(int windowWidth, int windowHeight);  // ✅ Adjusts to window resizing
    void shoot(Player& player);             // ✅ Dynamic shooting based on rotation

    // ✅ Core SFML Components
    sf::RenderWindow window;
    sf::View view;

    // ✅ Game Elements
    Player player1, player2;
    Map map;                                // ✅ Collision with map elements
    std::vector<Bullet> bullets;            // ✅ Handles all active bullets

    // ✅ UI Components
    sf::Font font;
    sf::Text controlsText;

    // ✅ Close Button Components (from `map` branch)
    sf::RectangleShape closeButton;
    sf::Text closeButtonText;
};

#endif
