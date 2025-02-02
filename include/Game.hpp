#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.hpp"
#include "Bullet.hpp"

class Game
{
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();
    void handleShooting();
    void handleResize(int windowWidth, int windowHeight);
    void shoot(Player &player);

    sf::RenderWindow window;
    sf::View view;
    Player player, player2;
    std::vector<Bullet> bullets;

    // For displaying controls
    sf::Font font;
    sf::Text controlsText;
};

#endif
