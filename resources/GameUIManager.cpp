#include "GameUIManager.h"
#include <iostream>
#include <cmath>

GameUIManager::GameUIManager()
    : displayingMessage(false),
      textGrowthSpeed(2.0f),           // Increased speed for better effect
      scaleFactorForFullCoverage(0.0f),
      currentScale(1.0f),
      initialCharSize(60)
{
}

bool GameUIManager::loadFont(const std::string& fontPath) {
    if (!font.loadFromFile("./fonts/NotoSansArmenian-VariableFont_wdth,wght.ttf")) {
        std::cerr << "Error: GameUIManager could not load font from: " << fontPath << std::endl;
        return false;
    }
    return true;
}

float GameUIManager::calculateScaleToFillWindow(const sf::RenderWindow& window) {
    sf::FloatRect textBounds = messageText.getLocalBounds();
    float textWidth = textBounds.width;
    float textHeight = textBounds.height;

    float windowWidth = static_cast<float>(window.getSize().x);
    float windowHeight = static_cast<float>(window.getSize().y);

    // Calculate what scale is needed to make text cover the entire window
    // We need the text to be big enough to cover from corner to corner
    float scaleX = windowWidth / textWidth;
    float scaleY = windowHeight / textHeight;
    
    // Use the larger scale and multiply by 2 to ensure complete coverage
    return std::max(scaleX, scaleY) * 2.0f;
}

void GameUIManager::showManagedMessage(const std::string& message, const sf::Color& color, unsigned int characterSize, const sf::RenderWindow& window) {
    if (font.getInfo().family.empty()) {
        std::cerr << "Error: Font not loaded in GameUIManager. Message cannot be displayed." << std::endl;
        return;
    }
    
    messageText.setFont(font);
    initialCharSize = characterSize;
    messageText.setString(message);
    messageText.setFillColor(color);
    messageText.setCharacterSize(initialCharSize);
    
    // Start with normal scale
    currentScale = 1.0f;
    messageText.setScale(currentScale, currentScale);

    // Find the center character and set origin there
    sf::FloatRect textBounds = messageText.getLocalBounds();
    float charCenterX, charCenterY;
    
    if (message == "YOU WIN!") {
        sf::Text tempText = messageText;
        tempText.setString("YOU ");
        float beforeW = tempText.getLocalBounds().width;
        
        tempText.setString("W");
        float wWidth = tempText.getLocalBounds().width;
        
        charCenterX = textBounds.left + beforeW + wWidth / 2.0f;
        charCenterY = textBounds.top + textBounds.height / 2.0f;
    }
    else if (message == "GAME OVER!") {
        sf::Text tempText = messageText;
        tempText.setString("GAME ");
        float beforeO = tempText.getLocalBounds().width;
        
        tempText.setString("O");
        float oWidth = tempText.getLocalBounds().width;
        
        charCenterX = textBounds.left + beforeO + oWidth / 2.0f;
        charCenterY = textBounds.top + textBounds.height / 2.0f;
    }
    else {
        charCenterX = textBounds.left + textBounds.width / 2.0f;
        charCenterY = textBounds.top + textBounds.height / 2.0f;
    }

    messageText.setOrigin(charCenterX, charCenterY);

    scaleFactorForFullCoverage = calculateScaleToFillWindow(window);

    displayingMessage = true;
}

void GameUIManager::update(float deltaTime, sf::RenderWindow& window) {
    if (!displayingMessage) {
        return;
    }

    currentScale += textGrowthSpeed * deltaTime;
    messageText.setScale(currentScale, currentScale);

    messageText.setPosition(static_cast<float>(window.getSize().x) / 2.0f,
                           static_cast<float>(window.getSize().y) / 2.0f);

    if (currentScale >= scaleFactorForFullCoverage / 4) {
        displayingMessage = false;
        window.close();
    }
}

void GameUIManager::draw(sf::RenderWindow& window) {
    if (displayingMessage) {
        window.draw(messageText);
    }
}

bool GameUIManager::isMessageActive() const {
    return displayingMessage;
}