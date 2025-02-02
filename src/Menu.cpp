#include "Menu.hpp"

Menu::Menu(float width, float height) {
    selectedItemIndex = 0;

    // ✅ Load background image
    if (!backgroundTexture.loadFromFile("assets/images/Background.jpg")) {
        // Handle error
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        width / backgroundSprite.getLocalBounds().width,
        height / backgroundSprite.getLocalBounds().height
    );

    // ✅ Load custom font
    if (!font.loadFromFile("assets/fonts/ARMY_RUST.ttf")) {
        // Handle error
    }

    // Initial menu items
    std::vector<std::string> items = {"Play", "Exit"};

    for (size_t i = 0; i < items.size(); i++) {
        sf::Text text;
        text.setFont(font);
        text.setString(items[i]);
        text.setCharacterSize(48);  // Larger size for bold effect
        text.setFillColor(i == selectedItemIndex ? sf::Color::Yellow : sf::Color::White);
        menuItems.push_back(text);
    }

    adjustMenuPositions(width, height); // Center the menu items
}


void Menu::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite); // ✅ Draw the background

    for (auto& item : menuItems) {
        window.draw(item); // Draw menu items on top
    }
}


void Menu::moveUp() {
    if (selectedItemIndex > 0) {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::moveDown() {
    if (selectedItemIndex < menuItems.size() - 1) {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}


int Menu::getSelectedItemIndex() {
    return selectedItemIndex;
}
int Menu::getItemIndexAtPosition(sf::Vector2f position) {
    for (size_t i = 0; i < menuItems.size(); i++) {
        if (menuItems[i].getGlobalBounds().contains(position)) {
            menuItems[selectedItemIndex].setFillColor(sf::Color::White); // Reset previous selection
            selectedItemIndex = i;
            menuItems[selectedItemIndex].setFillColor(sf::Color::Yellow); // Highlight hovered item
            return i;
        }
    }
    return -1;
}

void Menu::adjustMenuPositions(float width, float height) {
    float startY = height / 2 - (menuItems.size() * 30);  // Center vertically

    for (size_t i = 0; i < menuItems.size(); i++) {
        // ✅ Center based on text width
        float textWidth = menuItems[i].getLocalBounds().width;
        float centerX = (width - textWidth) / 2;

        menuItems[i].setPosition(centerX, startY + i * 80);  // Even vertical spacing
    }
}


void Menu::showRestartOption(bool show, float width, float height) {
    if (show && menuItems.size() == 2) {
        sf::Text restartText;
        restartText.setFont(font);
        restartText.setString("Restart");
        restartText.setCharacterSize(48);
        restartText.setFillColor(sf::Color::White);
        menuItems.insert(menuItems.end() - 1, restartText);
    } 
    else if (!show && menuItems.size() == 3) {
        menuItems.erase(menuItems.end() - 2);
    }
    // Now recenter with the *correct* window size
    adjustMenuPositions(width, height);
}



void Menu::onHover(sf::Vector2f mousePos) {
    for (size_t i = 0; i < menuItems.size(); i++) {
        sf::FloatRect bounds = menuItems[i].getGlobalBounds();

        if (bounds.contains(mousePos)) {
            // ✅ Apply hover effect
            menuItems[i].setFillColor(sf::Color::Yellow);  // Highlight the item
            menuItems[i].setScale(1.1f, 1.1f);             // Slightly enlarge the text
            selectedItemIndex = i;
        } else {
            // Revert to default when not hovering
            menuItems[i].setFillColor(sf::Color::White);
            menuItems[i].setScale(1.0f, 1.0f);
        }
    }
}

sf::Sprite Menu::getBackground() {
    return backgroundSprite;
}