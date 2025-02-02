#include "Game.hpp"
#include <cmath>    // For cos/sin
#include <algorithm> // For std::max

Game::Game()
    : window(sf::VideoMode(800, 600), "SFML Gunfight Game", sf::Style::Default),
      player1(20, 275, sf::Color::Green),
      player2(730, 275, sf::Color::Blue),
      map(),                 // Construct your map as needed
      menu(800, 600),       // Menu with given window size
      inMenu(true)          // Start in the menu
{
    // Basic window setup
    window.setFramerateLimit(60);

    // Setup the view for 800x600 initially
    view.setSize(800, 600);
    view.setCenter(400, 300);
    window.setView(view);

    // If you have a font, load it here (assuming "arial.ttf" or similar)
    // if (!font.loadFromFile("path/to/arial.ttf")) {
    //     // Handle error
    // }

    // Setup controls text (optional)
    controlsText.setFont(font);
    controlsText.setString("Press W/A/S/D or Arrow Keys to move. SPACE or ENTER to shoot.");
    controlsText.setCharacterSize(14);
    controlsText.setFillColor(sf::Color::White);
    controlsText.setPosition(10.f, static_cast<float>(window.getSize().y) - 20.f);

    // Setup “Menu” button (though we use the hamburger icon below)
    menuButton.setSize(sf::Vector2f(80, 30));
    menuButton.setFillColor(sf::Color::Blue);
    menuButton.setPosition(window.getSize().x - 90.f, 10.f);

    // Text inside the button
    menuButtonText.setFont(font);
    menuButtonText.setString("Menu");
    menuButtonText.setCharacterSize(16);
    menuButtonText.setFillColor(sf::Color::White);
    menuButtonText.setPosition(window.getSize().x - 75.f, 15.f);

    // Position players in the middle of the window
    player1.setPosition(20.f, window.getSize().y / 2.f - player1.getSize().y / 2.f);
    player2.setPosition(
        window.getSize().x - player2.getSize().x - 20.f,
        window.getSize().y / 2.f - player2.getSize().y / 2.f
    );
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
        // Close button
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        // Handle window resizing
        if (event.type == sf::Event::Resized) {
            handleResize(event.size.width, event.size.height);
        }

        // If we’re in the menu, handle menu logic
        if (inMenu) {
            handleMenuInput(event);

            // Mouse hover effect on menu items
            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);
                menu.onHover(mousePos);
            }
        }
        // If we’re in the game (not the menu)
        else {
            // Check if user clicked on the “hamburger” area
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);

                // A small bounding box for the hamburger icon
                sf::FloatRect hamburgerBounds(20.f, 20.f, 30.f, 20.f); 
                if (hamburgerBounds.contains(mousePos)) {
                    inMenu = true; // Open the menu
                }
            }

            // Handle shooting keys (Space, Enter)
            handleShooting();
        }
    }
}

void Game::update() {
    // Only update game elements if not in the menu
    if (!inMenu) {
        // Player movement & collision with the map
        player1.update(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D, window, map, player2);
        player2.update(sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right, window, map, player1);

        // Update bullets and handle collisions
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

    // If we’re in the menu, draw it
    if (inMenu) {
        window.draw(menu.getBackground());
        menu.draw(window);
    }
    // Otherwise, draw game elements
    else {
        // Draw map
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

        // Draw the “hamburger” icon in the corner
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
    static bool gameStarted = false; // Track if a game has ever started

    // Handle keyboard
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            menu.moveUp();
        }
        else if (event.key.code == sf::Keyboard::Down) {
            menu.moveDown();
        }
        else if (event.key.code == sf::Keyboard::Enter) {
            int selectedItem = menu.getSelectedItemIndex();
            if (selectedItem == 0) {     // Play
                inMenu = false;
                gameStarted = true;
                menu.showRestartOption(true);
            }
            else if (selectedItem == 1 && gameStarted) { // Restart
                restartGame();
            }
            else if ((selectedItem == 2 && gameStarted) || (selectedItem == 1 && !gameStarted)) {
                window.close();
            }
        }
    }
    // Handle mouse
    else if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);

            int selectedItem = menu.getItemIndexAtPosition(mousePos);
            if (selectedItem != -1) {
                if (selectedItem == 0) {     // Play
                    inMenu = false;
                    gameStarted = true;
                    menu.showRestartOption(true);
                }
                else if (selectedItem == 1 && gameStarted) { // Restart
                    restartGame();
                }
                else if ((selectedItem == 2 && gameStarted) || (selectedItem == 1 && !gameStarted)) {
                    window.close();
                }
            }
        }
    }
}

void Game::handleShooting() {
    // Press Space to shoot with player1
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        shoot(player1);
    }
    // Press Enter to shoot with player2
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        shoot(player2);
    }
}

// Spawns a bullet in the direction the player is facing
void Game::shoot(Player& player) {
    float angle = player.getRotation() * 3.14159265f / 180.0f;
    float dirX = std::cos(angle);
    float dirY = std::sin(angle);

    // Ensure bullet spawns a bit “in front” of the player
    float offset = std::max(player.getSize().x, player.getSize().y) / 2.f + 10.f;
    float bulletX = player.getPosition().x + dirX * offset;
    float bulletY = player.getPosition().y + dirY * offset;

    bullets.push_back(Bullet(bulletX, bulletY, dirX, dirY));
}

// Handle window resizing
void Game::handleResize(int windowWidth, int windowHeight) {
    // Adjust the view
    view.setSize(static_cast<float>(windowWidth), static_cast<float>(windowHeight));
    view.setCenter(static_cast<float>(windowWidth) / 2.f, static_cast<float>(windowHeight) / 2.f);
    window.setView(view);

    // Resize the map (if your Map supports this)
    map.resize(windowWidth, windowHeight);

    // Reposition players
    player1.setPosition(50.f, windowHeight / 2.f - player1.getSize().y / 2.f);
    player2.setPosition(windowWidth - player2.getSize().x - 20.f, 
                        windowHeight / 2.f - player2.getSize().y / 2.f);
    // You could adjust rotation if you need:
    // player2.setRotation(180.f);

    // Reposition UI elements
    menuButton.setPosition(windowWidth - 90.f, 10.f);
    menuButtonText.setPosition(windowWidth - 75.f, 15.f);
    controlsText.setPosition(10.f, static_cast<float>(windowHeight) - 20.f);

    // Let the Menu adjust
    menu.adjustMenuPositions(windowWidth, windowHeight);
}

// Reset positions/states without quitting
void Game::restartGame() {
    sf::Vector2f viewSize = view.getSize();
    sf::Vector2f viewCenter = view.getCenter();
    float windowWidth = viewSize.x;

    // Position players again
    player1.setPosition(20.f, viewCenter.y - player1.getSize().y / 2.f);
    player2.setPosition(windowWidth - player2.getSize().x - 20.f, 
                        viewCenter.y - player2.getSize().y / 2.f);

    // Clear all bullets
    bullets.clear();

    // Resume game
    inMenu = false;
}
