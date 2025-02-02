#include "Game.hpp"
#include <cmath>

Game::Game()
    : window(sf::VideoMode::getDesktopMode(), "SFML Gunfight Game", sf::Style::Fullscreen),
      player1(20, 275, sf::Color::Green),
      player2(730, 275, sf::Color::Blue) {

    window.setFramerateLimit(60);
    view.setSize(window.getSize().x, window.getSize().y);
    view.setCenter(window.getSize().x / 2, window.getSize().y / 2);
    window.setView(view);

    player1.setPosition(20, window.getSize().y / 2);
    player2.setPosition(window.getSize().x - 70, window.getSize().y / 2);
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        // ✅ Handle Window Resizing
        if (event.type == sf::Event::Resized) {
            handleResize(event.size.width, event.size.height);
        }
    }
    handleShooting();
}


void Game::update() {
    player1.update(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D, window, map, player2);
    player2.update(sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right, window, map, player1);

    for (auto it = bullets.begin(); it != bullets.end();) {
        it->update();

        // ✅ Bullet Collision with Map (Including Rotated Walls)
        if (map.checkCollision(it->getBounds())) {
            it = bullets.erase(it);  // Remove bullet if it hits any wall
            continue;
        }

        // ✅ Bullet Collision with Players
        if (it->getBounds().intersects(player1.getBounds())) {
            it = bullets.erase(it);
            continue;
        }

        if (it->getBounds().intersects(player2.getBounds())) {
            it = bullets.erase(it);
            continue;
        }

        ++it;  // Move to the next bullet
    }
}


void Game::render() {
    window.clear();
    map.draw(window);
    player1.draw(window);
    player2.draw(window);

    for (auto& bullet : bullets) {
        bullet.draw(window);
    }

    window.display();
}

void Game::handleShooting() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        shoot(player1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        shoot(player2);
    }
}

void Game::shoot(Player& player) {
    float angle = player.getRotation() * 3.14159265f / 180.0f;
    float dirX = cos(angle);
    float dirY = sin(angle);

    // ✅ Offset distance to ensure the bullet spawns outside the player's collision box
    float offset = std::max(player.getSize().x, player.getSize().y) / 2 + 10;  // Add 10 pixels buffer

    // ✅ Calculate bullet spawn position based on the player's rotation
    float bulletX = player.getPosition().x + dirX * offset;
    float bulletY = player.getPosition().y + dirY * offset;

    // ✅ Create and push the bullet
    bullets.push_back(Bullet(bulletX, bulletY, dirX, dirY));
}

void Game::handleResize(int windowWidth, int windowHeight) {
    view.setSize(windowWidth, windowHeight);
    view.setCenter(windowWidth / 2, windowHeight / 2);
    window.setView(view);

    map.resize(windowWidth, windowHeight);

    // ✅ Adjust player positions relative to the new window size
    player1.setPosition(20+30, windowHeight / 2 - player1.getSize().y / 2);
    player2.setPosition(windowWidth - player2.getSize().x , windowHeight / 2 - player2.getSize().y / 2);
    player2.setRotation(180);
}





