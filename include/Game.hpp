#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Map.hpp"
#include "Bullet.hpp"
#include <vector>

class Game {
public:
    Game();
    void run();

private:
    // ✅ Core SFML Components
    sf::RenderWindow window;
    sf::View view;

    // ✅ Game Elements
    Player player1, player2;
    Map map;
    std::vector<Bullet> bullets;

    // ✅ UI Components
    sf::Font font;
    sf::Text controlsText;

    // ✅ Close Button Components
    sf::RectangleShape closeButton;    // Close Button (Red Box)
    sf::Text closeButtonText;          // "X" Symbol Inside the Button

    // ✅ Core Game Loop Functions
    void processEvents();
    void update();
    void render();
    void handleShooting();
    void handleResize(int windowWidth, int windowHeight);
};

#endif // GAME_HPP
