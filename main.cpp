#include <iostream>
#include "./resources/Pacman.h"
#include "./resources/Block.h"  
#include "./resources/Ghost/Ghost.h"
#include "./resources/Dram.h"
#include "./resources/Map.h"
#include <thread>
#include <chrono>

int main() {
    Map map;
    map.loadLevel();

    sf::RenderWindow window(sf::VideoMode({1360, 690}), "Pac-Man in Armenia");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    int pac_frameIndex {};
    int ghost_frameIndex {};
    sf::Clock animationClock;
    float frameTime = 0.15f;
    sf::Clock gameLoopClock; // For delta time
    float deltaTime = 0.f;

    sf::Event::KeyEvent currKey {};
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
                    std::exit(0);
                }
            }
        }
        
        map.getPacman().PacmanMovement(currKey, map, deltaTime);    
        for (auto* ghost : map.getGhost()) ghost->move(map, map.getPacman(), deltaTime); 
        map.checkGameResult(window);

        if (animationClock.getElapsedTime().asSeconds() > frameTime) {
            pac_frameIndex = (pac_frameIndex + 1) % map.getPacman().getCurrDirection().size();
            ghost_frameIndex = (ghost_frameIndex + 1) % 2;
            animationClock.restart();
        }
        
        
        
        window.clear(sf::Color::Black);
        
        map.draw(window);
        map.getPacman().draw(window, pac_frameIndex);
        for (auto* ghost : map.getGhost())  ghost->draw(window, ghost_frameIndex);
        
        window.display();

    }
}
