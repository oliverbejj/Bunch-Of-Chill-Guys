#include "Game.hpp"
#include <cmath>      // For cos/sin
#include <algorithm>  // For std::max

Game::Game()
    : window(sf::VideoMode::getDesktopMode(), "SFML Gunfight Game", sf::Style::Fullscreen),
      // Keep the same Player constructors:
      player1(20, 275, sf::Color::Green),
      player2(730, 275, sf::Color::Blue),
      map(),
      // Construct the menu at fullscreen size
      menu(window.getSize().x, window.getSize().y),
      inMenu(true)
{
    // Lock the frame rate
    window.setFramerateLimit(60);

    // Setup the full screen view
    float screenWidth  = static_cast<float>(window.getSize().x);
    float screenHeight = static_cast<float>(window.getSize().y);
    view.setSize(screenWidth, screenHeight);
    view.setCenter(screenWidth / 2.f, screenHeight / 2.f);
    window.setView(view);

    // Load your font if needed:
    // if (!font.loadFromFile("path/to/arial.ttf")) {
    //     // Error handling
    // }

    // Controls text at the bottom
    controlsText.setFont(font);
    controlsText.setString("W/A/S/D or Arrows to move. SPACE or ENTER to shoot. Click top-left icon for Menu.");
    controlsText.setCharacterSize(14);
    controlsText.setFillColor(sf::Color::White);
    controlsText.setPosition(10.f, screenHeight - 25.f);

    // A “Menu” rectangle button (though we typically draw the hamburger icon in render)
    menuButton.setSize(sf::Vector2f(80.f, 30.f));
    menuButton.setFillColor(sf::Color::Blue);
    menuButton.setPosition(screenWidth - 90.f, 10.f);

    menuButtonText.setFont(font);
    menuButtonText.setString("Menu");
    menuButtonText.setCharacterSize(16);
    menuButtonText.setFillColor(sf::Color::White);
    menuButtonText.setPosition(screenWidth - 75.f, 15.f);

    // -------------------------------
    // PLAYER SPAWNS (slightly adjusted)
    // -------------------------------
    // Player 1 at x=50 so they're not too close to the edge,
    //   and center them vertically (minus half of their height).
    player1.setPosition(
        50.f,
        (screenHeight / 2.f) - (player1.getSize().y / 2.f)
    );

    // Player 2 on the right side, center vertically, rotate 180° to face left
    player2.setPosition(
        screenWidth - player2.getSize().x - 50.f,
        (screenHeight / 2.f) - (player2.getSize().y / 2.f)
    );
    player2.setRotation(180.f);  // Face left

    // Let the menu format itself for fullscreen
    menu.adjustMenuPositions(window.getSize().x, window.getSize().y);
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
        // If user tries to close, exit
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        // Handle runtime resizing (rare in fullscreen, but we keep the logic)
        if (event.type == sf::Event::Resized) {
            handleResize(event.size.width, event.size.height);
        }

        if (inMenu) {
            // If we're in the menu, handle menu keys/mouse
            handleMenuInput(event);

            // Mouse-over effect for menu items
            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);
                menu.onHover(mousePos);
            }
        }
        else {
            // Check if user clicked the “hamburger” in top-left corner
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);

                // The bounding box for the three bars
                sf::FloatRect hamburgerBounds(20.f, 20.f, 30.f, 20.f);
                if (hamburgerBounds.contains(mousePos)) {
                    inMenu = true;  // Open the menu
                }
            }
            // Shooting
            handleShooting();
        }
    }
}

void Game::update() {
    if (!inMenu) {
        // Move players with collision
        player1.update(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D, window, map, player2);
        player2.update(sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right, window, map, player1);

        // Update bullets
        for (auto it = bullets.begin(); it != bullets.end();) {
            it->update();

            // Bullet vs. Map
            if (map.checkCollision(it->getBounds())) {
                it = bullets.erase(it);
                continue;
            }

            // Bullet vs. Players
            if (it->getBounds().intersects(player1.getBounds())) {
                it = bullets.erase(it);
                continue;
            }
            if (it->getBounds().intersects(player2.getBounds())) {
                it = bullets.erase(it);
                continue;
            }
            ++it;
        }
    }
}

void Game::render() {
    window.clear();

    if (inMenu) {
        // Draw menu background/items
        window.draw(menu.getBackground());
        menu.draw(window);
    } 
    else {
        // Draw the map
        map.draw(window);

        // Draw players
        player1.draw(window);
        player2.draw(window);

        // Draw bullets
        for (auto& bullet : bullets) {
            bullet.draw(window);
        }

        // Draw controls text
        window.draw(controlsText);

        // “Hamburger” icon in top-left
        sf::RectangleShape bar1(sf::Vector2f(24.f, 4.f));
        sf::RectangleShape bar2(sf::Vector2f(24.f, 4.f));
        sf::RectangleShape bar3(sf::Vector2f(24.f, 4.f));

        bar1.setFillColor(sf::Color::White);
        bar2.setFillColor(sf::Color::White);
        bar3.setFillColor(sf::Color::White);

        bar1.setPosition(20.f, 20.f);
        bar2.setPosition(20.f, 28.f);
        bar3.setPosition(20.f, 36.f);

        window.draw(bar1);
        window.draw(bar2);
        window.draw(bar3);
    }

    window.display();
}

void Game::handleMenuInput(sf::Event event) {
    static bool gameStarted = false; // track if a game has started

    // Keyboard input for the menu
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            menu.moveUp();
        }
        else if (event.key.code == sf::Keyboard::Down) {
            menu.moveDown();
        }
        else if (event.key.code == sf::Keyboard::Enter) {
            int selectedItem = menu.getSelectedItemIndex();
            if (selectedItem == 0) { // Play
                inMenu = false;
                gameStarted = true;
                // Instead of menu.showRestartOption(true);
                menu.showRestartOption(true, window.getSize().x, window.getSize().y);

            }
            else if (selectedItem == 1 && gameStarted) { // Restart
                restartGame();
            }
            else if ((selectedItem == 2 && gameStarted) ||
                     (selectedItem == 1 && !gameStarted)) {
                window.close();
            }
        }
    }
    // Mouse input for the menu
    else if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);

            int selectedItem = menu.getItemIndexAtPosition(mousePos);
            if (selectedItem != -1) {
                if (selectedItem == 0) {  // Play
                    inMenu = false;
                    gameStarted = true;
                    // Instead of menu.showRestartOption(true);
                    menu.showRestartOption(true, window.getSize().x, window.getSize().y);

                }
                else if (selectedItem == 1 && gameStarted) { // Restart
                    restartGame();
                }
                else if ((selectedItem == 2 && gameStarted) ||
                         (selectedItem == 1 && !gameStarted)) {
                    window.close();
                }
            }
        }
    }
}

void Game::handleShooting() {
    // Player1 shoots with Space
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        shoot(player1);
    }
    // Player2 shoots with Enter
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        shoot(player2);
    }
}

// Spawns a bullet in the direction the player is facing
void Game::shoot(Player& player) {
    float angle = player.getRotation() * 3.14159265f / 180.0f;
    float dirX  = std::cos(angle);
    float dirY  = std::sin(angle);

    // Offset bullet so it doesn't spawn inside the player
    float offset = std::max(player.getSize().x, player.getSize().y) / 2.f + 10.f;
    float bulletX = player.getPosition().x + dirX * offset;
    float bulletY = player.getPosition().y + dirY * offset;

    bullets.push_back(Bullet(bulletX, bulletY, dirX, dirY));
}

// Handle a resize (fullscreen won't often get a resize event, but let's keep it)
void Game::handleResize(int windowWidth, int windowHeight) {
    view.setSize(static_cast<float>(windowWidth), static_cast<float>(windowHeight));
    view.setCenter(static_cast<float>(windowWidth) / 2.f,
                   static_cast<float>(windowHeight) / 2.f);
    window.setView(view);

    map.resize(windowWidth, windowHeight);

    // Reposition the UI
    menuButton.setPosition(windowWidth - 90.f, 10.f);
    menuButtonText.setPosition(windowWidth - 75.f, 15.f);
    controlsText.setPosition(10.f, static_cast<float>(windowHeight) - 25.f);

    // Let the menu recenter for the new size
    menu.adjustMenuPositions(windowWidth, windowHeight);

    // Reposition players similarly
    player1.setPosition(
        50.f,
        (windowHeight / 2.f) - (player1.getSize().y / 2.f)
    );
    // Player 2 on right, face left
    player2.setPosition(
        windowWidth - player2.getSize().x - 50.f,
        (windowHeight / 2.f) - (player2.getSize().y / 2.f)
    );
    player2.setRotation(180.f);
}

void Game::restartGame() {
    // Clear bullets and reposition players as if new game
    sf::Vector2f viewSize   = view.getSize();
    sf::Vector2f viewCenter = view.getCenter();
    float windowWidth       = viewSize.x;
    float windowHeight      = viewSize.y;

    // Put them at the same positions as constructor
    player1.setPosition(
        50.f,
        (windowHeight / 2.f) - (player1.getSize().y / 2.f)
    );
    player2.setPosition(
        windowWidth - player2.getSize().x - 50.f,
        (windowHeight / 2.f) - (player2.getSize().y / 2.f)
    );
    player1.setRotation(0.f);
    player2.setRotation(180.f);

    bullets.clear();
    inMenu = false;  // Resume the game
}
