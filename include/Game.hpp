#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.hpp"
#include "Bullet.hpp"
#include "Map.hpp"
#include "Menu.hpp"

class Game {
private:
    sf::RenderWindow window;
    sf::View view;
    Player player1;
    Player player2;
    Map map;
    Menu menu;
    bool inMenu;
    sf::Font font;
    sf::Text controlsText;
    std::vector<Bullet> bullets;

    // ✅ Health Bars and Round-End Text
    sf::RectangleShape healthBarP1, healthBarP2;
    sf::Text roundEndedText;

public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();
    void handleMenuInput(sf::Event event);
    void handleShooting();
    void shoot(Player& player);
    void handleResize(int windowWidth, int windowHeight);
    void restartGame();
};

#endif // GAME_HPP
