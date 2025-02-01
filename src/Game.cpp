#include "Game.hpp"

Game::Game()
    : window(sf::VideoMode(800, 600), "SFML Gunfight Game", sf::Style::Default),
      player1(20, 275, sf::Color::Green),     // Slightly further from the left edge
      player2(730, 275, sf::Color::Blue) {    // Slightly further from the right edge

    window.setFramerateLimit(60);

    view.setSize(800, 600);
    view.setCenter(400, 300);
    window.setView(view);

    // Adjust Player 2's position dynamically
    player2.setPosition(window.getSize().x - player2.getSize().x - 20, window.getSize().y / 2 - player2.getSize().y / 2);
    player1.setPosition(20, window.getSize().y / 2 - player1.getSize().y / 2);

    // Load font for displaying controls
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
        // Handle error if font doesn't load
    }

    controlsText.setFont(font);
    controlsText.setCharacterSize(14);
    controlsText.setFillColor(sf::Color::White);
    controlsText.setString("P1: Move (WASD), Shoot (Space) | P2: Move (Arrow Keys), Shoot (Enter)");
    controlsText.setPosition(10, window.getSize().y - 20);
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
        if (event.type == sf::Event::Resized) {
            handleResize(event.size.width, event.size.height);

            // Adjust players to stay near the edges
            player1.setPosition(20, window.getSize().y / 2 - player1.getSize().y / 2);  // Slightly from the left edge, vertically centered
            player2.setPosition(window.getSize().x - player2.getSize().x - 20, window.getSize().y / 2 - player2.getSize().y / 2);  // Slightly from the right edge, vertically centered

            // Adjust controls text position when resizing
            controlsText.setPosition(10, window.getSize().y - 20);
        }
    }
    handleShooting();
}

void Game::handleResize(int windowWidth, int windowHeight) {
    view.setSize(windowWidth, windowHeight);          // View size matches window size
    view.setCenter(windowWidth / 2, windowHeight / 2); // Center the view
    window.setView(view);
}

void Game::update() {
    player1.update(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D);
    player2.update(sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right);

    for (auto& bullet : bullets) {
        bullet.update();
    }
}

void Game::render() {
    window.clear();
    player1.draw(window);
    player2.draw(window);

    for (auto& bullet : bullets) {
        bullet.draw(window);
    }

    // Draw controls at the bottom of the screen
    window.draw(controlsText);

    window.display();
}

void Game::handleShooting() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        bullets.push_back(Bullet(player1.getPosition().x + 50, player1.getPosition().y + 25, 1, 0));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {  // Changed from RControl to Enter
        bullets.push_back(Bullet(player2.getPosition().x, player2.getPosition().y + 25, -1, 0));
    }
}
