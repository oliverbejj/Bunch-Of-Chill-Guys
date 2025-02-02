#include "Game.hpp"
#include <cmath>
#include <algorithm>
#include <iostream>

Game::Game()
    : window(sf::VideoMode::getDesktopMode(), "SFML Gunfight Game", sf::Style::Fullscreen),
      player1(20, 275, sf::Color::Green, "assets/soldier/soldier1_stand.png"),
      player2(730, 275, sf::Color::Blue, "assets/soldier/soldier1_stand.png"),
      map(),
      menu(window.getSize().x, window.getSize().y),
      inMenu(true)
{
    window.setFramerateLimit(60);

    font.loadFromFile("assets/fonts/ARMY_RUST.ttf");
    controlsText.setFont(font);
    controlsText.setString("Player 1: W, A, S, D to move, Space to shoot - Player 2: Arrow keys to move, Enter to shoot");
    controlsText.setCharacterSize(14);
    controlsText.setFillColor(sf::Color::White);

    // ✅ Health Bar Initialization (Positioning left to you)
    healthBarP1.setSize(sf::Vector2f(100, 10));
    healthBarP1.setFillColor(sf::Color::Green);

    healthBarP1.setPosition(5, 5);  // Example position, adjust as needed

    healthBarP2.setSize(sf::Vector2f(100, 10));
    healthBarP2.setFillColor(sf::Color::Green);
    // ✅ You can set Player 2's health bar position here:
    healthBarP2.setPosition(window.getSize().x -105, 5);  // Example position, adjust as needed
    

    // ✅ Round-Ended Text
    roundEndedText.setFont(font);
    roundEndedText.setCharacterSize(24);
    roundEndedText.setFillColor(sf::Color::Blue);
    roundEndedText.setString("");

    player2.setShapeColor(sf::Color::Red);


    // ✅ Round and Score Display Initialization
    roundText.setFont(font);
    roundText.setCharacterSize(20);
    roundText.setFillColor(sf::Color::White);
    roundText.setPosition(window.getSize().x / 2-10, -5); // Centered at the top

    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(window.getSize().x / 2 -5 , 30); // Below the round text

    updateScoreDisplay(); // Initialize display with current scores

    // ✅ Load background music
    if (!gameMusic.openFromFile("assets/background.wav")) {
        std::cerr << "Failed to load game_music.ogg" << std::endl;
    }
    gameMusic.setLoop(true);
    gameMusic.setVolume(50);
    gameMusic.play();


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
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::Resized) {
            handleResize(event.size.width, event.size.height);
        }

        if (inMenu) {
            handleMenuInput(event);
        } else {
            // ✅ Handle hamburger icon click
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);

                // Bounding box for the hamburger icon
                sf::FloatRect hamburgerBounds(20.f, 20.f, 30.f, 20.f);
                if (hamburgerBounds.contains(mousePos)) {
                    inMenu = true;  // ✅ Open the menu when clicked
                }
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            inMenu = !inMenu;  // Toggle menu with Escape key
            }
            handleShooting();
        }
    }
}



void Game::update() {
    if (!inMenu) {
        player1.update(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D, window, map, player2);
        player2.update(sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right, window, map, player1);

        for (auto it = bullets.begin(); it != bullets.end();) {
            it->update();

            if (map.checkCollision(it->getBounds())) {
                it = bullets.erase(it);
                continue;
            }

            if (it->getBounds().intersects(player1.getBounds())) {
                player1.takeDamage(5);  // ✅ Apply damage
                it = bullets.erase(it);
                if (player1.isDead())
                {
                    roundEndedText.setString("Round Ended: Player 2 Wins!");
                    restartGame();
                    player2Score++;               // ✅ Increment Player 2's score
                    updateScoreDisplay(); 
                } // ✅ Round-End
                continue;
            }

            if (it->getBounds().intersects(player2.getBounds())) {
                player2.takeDamage(5);  // ✅ Apply damage
                it = bullets.erase(it);
                if (player2.isDead())
                {
                    roundEndedText.setString("Round Ended: Player 1 Wins!");
                    restartGame();
                    player1Score++;               // ✅ Increment Player 1's score
                    updateScoreDisplay();         // ✅ Update display
                } // ✅ Round-End
                continue;
            }
            ++it;
        }

        // ✅ Update Health Bars (Positioning left to you)
        healthBarP1.setSize(sf::Vector2f(player1.getHealth(), 10));
        healthBarP2.setSize(sf::Vector2f(player2.getHealth(), 10));
    }
}
void Game::render() {
    // Game.cpp - Inside Game::render()
window.clear();

if (inMenu) {
    menu.draw(window);
} else {
    map.draw(window);
    player1.draw(window);
    player2.draw(window);

    for (auto& bullet : bullets)
        bullet.draw(window);

    window.draw(controlsText);

    // ✅ Draw Health Bars
    window.draw(healthBarP1);
    window.draw(healthBarP2);

    // ✅ Draw Round End Indicator
    window.draw(roundEndedText);

    // ✅ Draw Hamburger Menu Icon
    sf::RectangleShape bar1(sf::Vector2f(24.f, 4.f));
    sf::RectangleShape bar2(sf::Vector2f(24.f, 4.f));
    sf::RectangleShape bar3(sf::Vector2f(24.f, 4.f));

    bar1.setFillColor(sf::Color::White);
    bar2.setFillColor(sf::Color::White);
    bar3.setFillColor(sf::Color::White);

    bar1.setPosition(25.f, 25.f);
    bar2.setPosition(25.f, 33.f);
    bar3.setPosition(25.f, 41.f);

    window.draw(bar1);
    window.draw(bar2);
    window.draw(bar3);

    window.draw(roundText);
    window.draw(scoreText);

}

window.display();

}


void Game::restartGame() {

    roundCount++; // ✅ Increment round counter

    player1.setPosition(50.f, (window.getSize().y / 2.f) - (player1.getSize().y / 2.f));
    player2.setPosition(window.getSize().x - player2.getSize().x, (window.getSize().y / 2.f) - (player2.getSize().y / 2.f));
    player1.setRotation(0);
    player2.setRotation(180);

    // ✅ Reset health for both players
    player1.resetHealth();
    player2.resetHealth();

    // ✅ Reset health bars to full size
    healthBarP1.setSize(sf::Vector2f(100, 10));  // Full health for Player 1
    healthBarP2.setSize(sf::Vector2f(100, 10));  // Full health for Player 2



    bullets.clear();
    roundEndedText.setString("");
    inMenu = false;

    updateScoreDisplay(); // ✅ Update score display
}

void Game::shoot(Player& player) {
    float angle = player.getRotation() * 3.14159265f / 180.0f;
    float dirX = std::cos(angle);
    float dirY = std::sin(angle);

    float offset = std::max(player.getSize().x, player.getSize().y) / 2.f + 10.f;
    float bulletX = player.getPosition().x + dirX * offset;
    float bulletY = player.getPosition().y + dirY * offset;

    bullets.emplace_back(bulletX, bulletY, dirX, dirY);
}

void Game::handleMenuInput(sf::Event event) {
    static bool gameStarted = false; // Track if a game has started

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            menu.moveUp();
        } 
        else if (event.key.code == sf::Keyboard::Down) {
            menu.moveDown();
        } 
        else if (event.key.code == sf::Keyboard::Enter) {
            int selectedItem = menu.getSelectedItemIndex();
            if (selectedItem == 0) {  // Play
                inMenu = false;
                gameStarted = true;
                menu.showRestartOption(true, window.getSize().x, window.getSize().y);
            } 
            else if (selectedItem == 1 && gameStarted) {  // Restart
                restartGame();
            } 
            else if ((selectedItem == 2 && gameStarted) ||
                     (selectedItem == 1 && !gameStarted)) {
                window.close();
            }
        }
    } 
    else if (event.type == sf::Event::MouseMoved) {
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);
        menu.onHover(mousePos);  // ✅ Hover effect restored
    }
    else if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);

            int selectedItem = menu.getItemIndexAtPosition(mousePos);
            if (selectedItem != -1) {
                if (selectedItem == 0) {  // Play
                    inMenu = false;
                    gameStarted = true;
                    menu.showRestartOption(true, window.getSize().x, window.getSize().y);
                } 
                else if (selectedItem == 1 && gameStarted) {  // Restart
                    restartGame();
                } 
                else if ((selectedItem == 2 && gameStarted) ||
                         (selectedItem == 1 && !gameStarted)) {
                    window.close();
                }
            }
        }
    }
}  // ✅ Closing brace fixed


void Game::handleShooting() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        shoot(player1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        shoot(player2);
    }
}
void Game::handleResize(int windowWidth, int windowHeight) {
    view.setSize(static_cast<float>(windowWidth), static_cast<float>(windowHeight));
    view.setCenter(windowWidth / 2.f, windowHeight / 2.f);
    window.setView(view);

    // ✅ Map resizing restored to original behavior
    map.resize(windowWidth, windowHeight);

    // Adjust UI elements
    controlsText.setPosition(10.f, windowHeight - 20.f);
    menu.adjustMenuPositions(windowWidth, windowHeight);

    // Player positions restored
    player1.setPosition(50.f, (windowHeight / 2.f) - (player1.getSize().y / 2.f));
    player2.setPosition(windowWidth - player2.getSize().x, (windowHeight / 2.f) - (player2.getSize().y / 2.f));
    player2.setRotation(180.f);
}



void Game::updateScoreDisplay() {
    roundText.setString("Round: " + std::to_string(roundCount));
    scoreText.setString(std::to_string(player1Score) + "  - | -  " +
                         std::to_string(player2Score));
}

