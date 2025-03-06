#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.hpp"
#include "Bullet.hpp"
#include "Map.hpp"
#include "Menu.hpp"
#include <SFML/Audio.hpp>

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

    // Health Bars and Round-End Text
    sf::RectangleShape healthBarP1, healthBarP2;
    sf::Text roundEndedText;

    void updateScoreDisplay();

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

    int roundCount = 0;       // Total rounds played
    int player1Score = 0;     // Player 1's score
    int player2Score = 0;     // Player 2's score

    sf::Text roundText;       // Displays the current round number
    sf::Text scoreText;       // Displays both players' scores

    sf::Music gameMusic;      // Background music
};

#endif 
