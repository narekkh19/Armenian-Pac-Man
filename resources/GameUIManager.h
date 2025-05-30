#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class GameUIManager {
public:
    GameUIManager();
    bool loadFont(const std::string& fontPath);
    void showManagedMessage(const std::string& message, const sf::Color& color, unsigned int characterSize, const sf::RenderWindow& window);
    void update(float deltaTime, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    bool isMessageActive() const;

private:
    sf::Font font;
    sf::Text messageText;
    bool displayingMessage;
    float textGrowthSpeed;
    float scaleFactorForFullCoverage; // This will now be calculated dynamically
    float currentScale;
    unsigned int initialCharSize;
    
    // Helper to calculate the scale needed to fill the screen
    float calculateScaleToFillWindow(const sf::RenderWindow& window);
};