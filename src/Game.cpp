#include "Game.hpp"

Game::Game()
    : window(sf::VideoMode(800, 600), "SFML Gunfight Game", sf::Style::Default),
      player1(20, 275, sf::Color::Green),
      player2(730, 275, sf::Color::Blue),
      menu(800, 600),
      inMenu(true) {

    window.setFramerateLimit(60);

    view.setSize(800, 600);
    view.setCenter(400, 300);
    window.setView(view);

    // Menu Button Setup
    menuButton.setSize(sf::Vector2f(80, 30));
    menuButton.setFillColor(sf::Color::Blue);
    menuButton.setPosition(window.getSize().x - 90, 10); // Top-right corner

    menuButtonText.setFont(font);
    menuButtonText.setString("Menu");
    menuButtonText.setCharacterSize(16);
    menuButtonText.setFillColor(sf::Color::White);
    menuButtonText.setPosition(window.getSize().x - 75, 15); // Centered inside the button

    player2.setPosition(window.getSize().x - player2.getSize().x - 20, window.getSize().y / 2 - player2.getSize().y / 2);
    player1.setPosition(20, window.getSize().y / 2 - player1.getSize().y / 2);
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

        if (inMenu) {
            handleMenuInput(event);

            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);
                menu.onHover(mousePos);
            }
        } else {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);

                // ✅ Detect clicks covering the entire button area (all lines)
                sf::FloatRect buttonBounds(20, 20, 30, 20); // Covers all three bars vertically

                if (buttonBounds.contains(mousePos)) {
                    inMenu = true;
                }
            }

            handleShooting();
        }
    }
}


void Game::handleMenuInput(sf::Event event) {
    static bool gameStarted = false; // Track if a game has started

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            menu.moveUp();
        } else if (event.key.code == sf::Keyboard::Down) {
            menu.moveDown();
        } else if (event.key.code == sf::Keyboard::Enter) {
            int selectedItem = menu.getSelectedItemIndex();
            if (selectedItem == 0) {  // Play
                inMenu = false;
                gameStarted = true;  // Mark the game as started
                menu.showRestartOption(true); // Show Restart option
            } else if (selectedItem == 1 && gameStarted) {  // Restart (only if a game has started)
                restartGame();
            } else if ((selectedItem == 2 && gameStarted) || (selectedItem == 1 && !gameStarted)) {  // Exit
                window.close();
            }
        }
    } else if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            // Convert mouse position to world coordinates
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);

            int selectedItem = menu.getItemIndexAtPosition(mousePos);
            if (selectedItem != -1) {
                if (selectedItem == 0) {  // Play
                    inMenu = false;
                    gameStarted = true;  // Mark the game as started
                    menu.showRestartOption(true); // Show Restart option
                } else if (selectedItem == 1 && gameStarted) {  // Restart (only if a game has started)
                    restartGame();
                } else if ((selectedItem == 2 && gameStarted) || (selectedItem == 1 && !gameStarted)) {  // Exit
                    window.close();
                }
            }
        }
    }
}



void Game::handleResize(int windowWidth, int windowHeight) {
    view.setSize(windowWidth, windowHeight);
    view.setCenter(windowWidth / 2, windowHeight / 2);
    window.setView(view);

    menuButton.setPosition(windowWidth - 90, 10);
    menuButtonText.setPosition(windowWidth - 75, 15);
    controlsText.setPosition(10, windowHeight - 20);

    // ✅ Adjust menu positions when the window is resized
    menu.adjustMenuPositions(windowWidth, windowHeight);
}






void Game::update() {
    if (!inMenu) {
        player1.update(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D, window);
        player2.update(sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right, window);

        for (auto& bullet : bullets) {
            bullet.update();
        }
    }
}

void Game::render() {
    window.clear();

    if (inMenu) {
        window.draw(menu.getBackground());
        menu.draw(window);
    } else {
        player1.draw(window);
        player2.draw(window);

        for (auto& bullet : bullets) {
            bullet.draw(window);
        }

        window.draw(controlsText);

        // ✅ Draw Menu Button as Three Bars (Hamburger Icon)
        sf::RectangleShape bar1(sf::Vector2f(24, 4));  // Less stretched horizontally
        sf::RectangleShape bar2(sf::Vector2f(24, 4));
        sf::RectangleShape bar3(sf::Vector2f(24, 4));

        bar1.setFillColor(sf::Color::White);
        bar2.setFillColor(sf::Color::White);
        bar3.setFillColor(sf::Color::White);

        bar1.setPosition(20, 20);
        bar2.setPosition(20, 28); // Increased separation
        bar3.setPosition(20, 36);

        window.draw(bar1);
        window.draw(bar2);
        window.draw(bar3);
    }

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
void Game::restartGame() {
    sf::Vector2f viewSize = view.getSize();    // ✅ Get current view size
    sf::Vector2f viewCenter = view.getCenter(); // ✅ Get view center

    float windowWidth = viewSize.x;

    // ✅ Correctly position players relative to the current view
    player1.setPosition(20, viewCenter.y - player1.getSize().y / 2);
    player2.setPosition(windowWidth - player2.getSize().x - 20, viewCenter.y - player2.getSize().y / 2);

    bullets.clear();  // Clear all bullets
    inMenu = false;   // Resume the game
}


