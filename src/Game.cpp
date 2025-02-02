#include "Game.hpp"

Game::Game()
    : window(sf::VideoMode::getDesktopMode(), "SFML Gunfight Game", sf::Style::Fullscreen),
      player1(20, 275, sf::Color::Green),
      player2(730, 275, sf::Color::Blue) {

    window.setFramerateLimit(60);

    // ✅ Fullscreen View Setup
    view.setSize(window.getSize().x, window.getSize().y);
    view.setCenter(window.getSize().x / 2, window.getSize().y / 2);
    window.setView(view);

    // ✅ Player Positions
    player1.setPosition(20, window.getSize().y / 2 - player1.getSize().y / 2);
    player2.setPosition(window.getSize().x - player2.getSize().x - 20, window.getSize().y / 2 - player2.getSize().y / 2);

    // ✅ Load Font
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
        // Handle error if font doesn't load
    }

    controlsText.setFont(font);
    controlsText.setCharacterSize(14);
    controlsText.setFillColor(sf::Color::White);
    controlsText.setString("P1: Move (WASD), Shoot (Space) | P2: Move (Arrow Keys), Shoot (Enter)");
    controlsText.setPosition(10, window.getSize().y - 20);

    // ✅ Close Button (Top-Right Corner)
    closeButton.setSize(sf::Vector2f(30, 30));
    closeButton.setFillColor(sf::Color::Red);
    closeButton.setOutlineThickness(2);
    closeButton.setOutlineColor(sf::Color::White);
    closeButton.setPosition(window.getSize().x - 40, 10);  // Position near top-right

    closeButtonText.setFont(font);
    closeButtonText.setCharacterSize(20);
    closeButtonText.setFillColor(sf::Color::White);
    closeButtonText.setString("X");
    closeButtonText.setPosition(closeButton.getPosition().x + 7, closeButton.getPosition().y - 2);
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

        // ✅ Close the game when ESC is pressed
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            window.close();

        // ✅ Detect Mouse Click on Close Button
        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (closeButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                window.close();  // Close the window if the button is clicked
            }
        }

        if (event.type == sf::Event::Resized) {
            handleResize(event.size.width, event.size.height);

            player1.setPosition(20, window.getSize().y / 2 - player1.getSize().y / 2);
            player2.setPosition(window.getSize().x - player2.getSize().x - 20, window.getSize().y / 2 - player2.getSize().y / 2);

            controlsText.setPosition(10, window.getSize().y - 20);

            // ✅ Adjust Close Button on Resize
            closeButton.setPosition(window.getSize().x - 40, 10);
            closeButtonText.setPosition(closeButton.getPosition().x + 7, closeButton.getPosition().y - 2);
        }
    }
    handleShooting();
}

void Game::handleResize(int windowWidth, int windowHeight) {
    view.setSize(windowWidth, windowHeight);
    view.setCenter(windowWidth / 2, windowHeight / 2);
    window.setView(view);

    map.resize(windowWidth, windowHeight);  // Adjust the map for new dimensions
}

void Game::update() {
    player1.update(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D, window, map);
    player2.update(sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right, window, map);

    if (map.checkCollision(player1.getBounds())) {
        player1.undoMove();
    }

    if (map.checkCollision(player2.getBounds())) {
        player2.undoMove();
    }

    for (auto it = bullets.begin(); it != bullets.end();) {
        it->update();
        if (map.checkCollision(it->getBounds())) {
            it = bullets.erase(it);
        } else {
            ++it;
        }
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

    // ✅ Draw Close Button
    window.draw(closeButton);
    window.draw(closeButtonText);

    window.draw(controlsText);
    window.display();
}

void Game::handleShooting() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        bullets.push_back(Bullet(player1.getPosition().x + 50, player1.getPosition().y + 25, 1, 0));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
        bullets.push_back(Bullet(player2.getPosition().x, player2.getPosition().y + 25, -1, 0));
    }
}
