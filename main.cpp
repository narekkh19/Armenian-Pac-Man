#include <iostream>
#include "./resources/Pacman.h"
#include "./resources/TufiBlock.h"  
#include "./resources/Ghost.h"
#include "./resources/Dram.h"
#include "./resources/Map.h"
#include <thread>
#include <chrono>

int main() {
    Map map;
    map.loadLevel();

    sf::RenderWindow window(sf::VideoMode({1360, 690}), "Pac-Man in Armenia");
    int pac_frameIndex {};
    int ghost_frameIndex {};
    sf::Clock animationClock;
    float frameTime = 0.15f;


    sf::Event::KeyEvent currKey {};
    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                currKey.code = event.key.code;
            }
        }
        map.getPacman().PacmanMovement(currKey, map);    
        for (auto& ghost : map.getGhost())  ghost.GhostMovement(map);
        
        if (animationClock.getElapsedTime().asSeconds() > frameTime) {
            pac_frameIndex = (pac_frameIndex + 1) % map.getPacman().getCurrDirection().size();
            ghost_frameIndex = (ghost_frameIndex + 1) % map.getGhost()[0].getCurrDirection().size();
            animationClock.restart();
        }



        window.clear(sf::Color::Black);

        map.draw(window);
        map.getPacman().draw(window, pac_frameIndex);
        for (auto& ghost : map.getGhost())  ghost.draw(window, ghost_frameIndex);
        
        window.display();

    }
}
