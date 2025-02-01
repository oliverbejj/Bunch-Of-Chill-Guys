#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Gunfight Game");
    window.setFramerateLimit(60);

    // Player representation
    sf::RectangleShape player(sf::Vector2f(50.f, 50.f));
    player.setFillColor(sf::Color::Green);
    player.setPosition(375.f, 275.f);

    float speed = 5.0f;

    // Adding Text
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
        // Fallback if the font doesn't load
        return -1;
    }
    sf::Text text("SFML Hackathon Test!", font, 24);
    text.setFillColor(sf::Color::White);
    text.setPosition(10.f, 10.f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Player Movement (WASD)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            player.move(0, -speed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            player.move(0, speed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            player.move(-speed, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            player.move(speed, 0);

        window.clear(sf::Color::Black);
        window.draw(player);
        window.draw(text); // Draw the text
        window.display();
    }

    return 0;
}
