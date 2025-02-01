#include "Menu.hpp"

Menu::Menu(float width, float height) {
    selectedItemIndex = 0;

    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
        // Handle error
    }

    std::vector<std::string> items = {"Play", "Exit"};  // ✅ Only Play and Exit initially

    for (size_t i = 0; i < items.size(); i++) {
        sf::Text text;
        text.setFont(font);
        text.setString(items[i]);
        text.setCharacterSize(36);
        text.setPosition(width / 2 - 50, height / 2 + i * 60);
        text.setFillColor(i == selectedItemIndex ? sf::Color::Red : sf::Color::White);
        menuItems.push_back(text);
    }
}


void Menu::draw(sf::RenderWindow& window) {
    for (auto& item : menuItems) {
        window.draw(item);
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
            return i;
        }
    }
    return -1; // No item was clicked
}
void Menu::adjustMenuPositions(float width, float height) {
    float centerX = width / 2 - 50;  // Center horizontally
    float startY = height / 2 - (menuItems.size() * 30);  // Center vertically based on the number of items

    for (size_t i = 0; i < menuItems.size(); i++) {
        menuItems[i].setPosition(centerX, startY + i * 60);  // Even vertical spacing
    }
}


void Menu::showRestartOption(bool show) {
    showRestart = show;

    if (show && menuItems.size() == 2) {
        sf::Text restartText;
        restartText.setFont(font);
        restartText.setString("Restart");
        restartText.setCharacterSize(36);
        restartText.setFillColor(sf::Color::White);

        menuItems.insert(menuItems.end() - 1, restartText);
    } 
    else if (!show && menuItems.size() == 3) {
        menuItems.erase(menuItems.end() - 2);
    }

    // ✅ Re-center the menu after changes
    adjustMenuPositions(800, 600);
}

