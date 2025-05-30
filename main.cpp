#include <iostream>
#include "SFML/Graphics.hpp"
#include "./resources/Pacman.h"    // Your Pacman header
#include "./resources/Map.h"       // Your Map header
#include "./resources/GameUIManager.h"         // Include the new UI Manager
// ... other necessary includes ...
#include <cstdlib>

int main() {
    sf::RenderWindow window(sf::VideoMode({1360, 690}), "Pac-Man with UI Manager");
    Map map;
    map.loadLevel();

    GameUIManager uiManager; // Create an instance of the UI Manager
    // IMPORTANT: Replace "arial.ttf" with the path to your font file!
    if (!uiManager.loadFont("arial.ttf")) {
        return EXIT_FAILURE; // Exit if font fails to load
    }

    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    int pac_frameIndex = 0;
    int ghost_frameIndex = 0;
    sf::Clock animationClock;
    float frameTime = 0.15f;
    sf::Clock gameLoopClock;
    float deltaTime = 0.f;
    sf::Event::KeyEvent currKey {};

    bool gameHasEnded = false; // New flag to control overall game end state

    while (window.isOpen()) {
        deltaTime = gameLoopClock.restart().asSeconds();
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                currKey.code = event.key.code;
                if (event.key.code == sf::Keyboard::W && event.key.control) {
                    window.close();
                }
            }
        }

        if (!gameHasEnded) { // Only update game logic if game hasn't ended
            map.getPacman().PacmanMovement(currKey, map, deltaTime);
            for (auto* ghost : map.getGhost()) {
                 // Adjust for Inky if its move signature needs blinkyPos
                ghost->move(map, map.getPacman(), deltaTime);
            }
            map.checkGameResult(window); // This will set Pacman's internal win/loss state

            // Check Pacman's state and trigger UI message if needed
            if (map.getPacman().isDead()) {
                uiManager.showManagedMessage("GAME OVER", sf::Color::Black, 100, window);
                gameHasEnded = true; // Mark that the game ending sequence has started
            } else if (map.getPacman().hasWon()) {
                uiManager.showManagedMessage("YOU WIN!", sf::Color::Black, 100, window);
                gameHasEnded = true; // Mark that the game ending sequence has started
            }
        }

        // Update the UI Manager (handles message animation and window closing)
        
        if (animationClock.getElapsedTime().asSeconds() > frameTime) {
            if (!map.getPacman().getCurrDirection().empty()) {
                pac_frameIndex = (pac_frameIndex + 1) % map.getPacman().getCurrDirection().size();
            }
            ghost_frameIndex = (ghost_frameIndex + 1) % 2;
            animationClock.restart();
        }
        
        window.clear(sf::Color::Black);
        map.draw(window);
        bool PacmanAnimationEnded = map.getPacman().draw(window, pac_frameIndex); // Pacman draws its own win/lose animation
        for (auto* ghost : map.getGhost()) {
            ghost->draw(window, ghost_frameIndex);
        }
        if (PacmanAnimationEnded) uiManager.update(deltaTime, window);
        if (PacmanAnimationEnded) uiManager.draw(window); // Draw the UI message on top
        window.display();
    }



    return EXIT_SUCCESS;
}