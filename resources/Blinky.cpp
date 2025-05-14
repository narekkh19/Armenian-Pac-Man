#include "Blinky.h"
#include <iostream>


int Blinky::manhattanDist(int x1, int y1, int x2, int y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}
std::pair<Directions, sf::Vector2f> Blinky::shortestDirectiontoPacman(Map& map, const sf::Vector2f& pacmanPos) {
    int ind_x = static_cast<int>(currPos.x) / tile_x;
    int ind_y = static_cast<int>(currPos.y) / tile_y;

    int pac_x = static_cast<int>(pacmanPos.x) / tile_x;
    int pac_y = static_cast<int>(pacmanPos.y) / tile_y;

    int minDist = std::numeric_limits<int>::max();
    Directions bestDirection = Directions::None;

    sf::Vector2f resultingTargetPixelPos(static_cast<float>(ind_x * tile_x), static_cast<float>(ind_y * tile_y));

    std::vector<std::pair<int, int>> dirs_tile_offsets = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};


    for (auto [dtx, dty] : dirs_tile_offsets) { 
        int next_potential_tile_x = ind_x + dtx;
        int next_potential_tile_y = ind_y + dty;

        if (isValidPosition(next_potential_tile_x, next_potential_tile_y, map)) { 
            int current_distance_to_pacman = manhattanDist(next_potential_tile_x, next_potential_tile_y, pac_x, pac_y);

            if (current_distance_to_pacman < minDist) {
                minDist = current_distance_to_pacman;
                resultingTargetPixelPos = sf::Vector2f(static_cast<float>(next_potential_tile_x * tile_x),
                                                     static_cast<float>(next_potential_tile_y * tile_y));

                if (dtx == -1 && dty == 0) bestDirection = Directions::Left;
                else if (dtx == 1 && dty == 0) bestDirection = Directions::Right;
                else if (dtx == 0 && dty == -1) bestDirection = Directions::Up;  
                else if (dtx == 0 && dty == 1) bestDirection = Directions::Down; 
            }
        }
    }
    return {bestDirection, resultingTargetPixelPos};
}

void Blinky::move(Map& map, Pacman& pac, float deltaTime) {
     if (moveProgress >= 1.f) {
        auto pacmanPos = pac.getCurrPosition();
        auto targetInfo = shortestDirectiontoPacman(map, pacmanPos);
        currDir = targetInfo.first;
        startPos = currPos;
        targetPos = targetInfo.second;
        
        moveProgress = 0.f;
    } 

    if (moveProgress < 1.f) {
        float progressDelta = deltaTime / moveDuration;
        moveProgress += progressDelta;
        currPos = startPos + (targetPos - startPos) * moveProgress;
        if (moveProgress > 1.f) moveProgress = 1.f;
        
        for (auto& spr : getCurrDirection()) spr.setPosition(currPos);
        
        if (moveProgress == 1.f) {
            currPos = targetPos;
        }
    }
}


