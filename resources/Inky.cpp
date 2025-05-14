#include "Inky.h"
#include <iostream>


int Inky::manhattanDist(int x1, int y1, int x2, int y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}


std::pair<int, int> Inky::manhattanDistCoord(int x1, int y1, int x2, int y2) {
    return {std::abs(x1 - x2), std::abs(y1 - y2)};
}


std::pair<Directions, sf::Vector2f> Inky::InkysUnpredictableLogic(Map& map, Pacman& pac) {
    int ind_x = currPos.x / tile_x;
    int ind_y = currPos.y / tile_y;
    
    auto pacmanPos = pac.getCurrPosition();
    int pac_x = pacmanPos.x / tile_x;
    int pac_y = pacmanPos.y / tile_y;

    auto desired = manhattanDistCoord(ind_x, ind_y, pac_x, pac_y);

    sf::Vector2f finalDesired = sf::Vector2f(2 * desired.first * tile_x, 2 * desired.second* tile_y);

    int fdes_x = finalDesired.x / tile_x;
    int fdes_y = finalDesired.y / tile_y;
    
    int minDist = std::numeric_limits<int>::max();
    Directions bestDirection = Directions::None; 

    // Define possible directions: up, down, left, right
    std::vector<std::pair<int, int>> dirs {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    sf::Vector2f targetPos;

    int i = 0;
    for (auto [dx, dy] : dirs) {
        ++i;
        int curr_dist = manhattanDist(dx + ind_x, dy + ind_y, fdes_x, fdes_y);

        if (isValidPosition(dx + ind_x, dy + ind_y, map)) {
            if (curr_dist < minDist) {
                minDist = curr_dist;
                targetPos = currPos + sf::Vector2f(dx * tile_x, dy * tile_y);
                bestDirection = static_cast<Directions>(i - 1);
            }
        }
    }
    
    return {bestDirection, targetPos};

}


void Inky::move(Map& map, Pacman& pac, float deltaTime) {

     if (moveProgress >= 1.f) {
        auto targetInfo = InkysUnpredictableLogic(map, pac);
        currDir = targetInfo.first;
        startPos = currPos;
        targetPos = targetInfo.second;

        moveProgress = 0.f;
        
    } 
    if (moveProgress < 1.f) {
        float progressDelta = deltaTime / moveDuration;
        moveProgress += progressDelta;
        currPos = startPos + (targetPos - startPos) *  moveProgress;
        if (moveProgress > 1.f) moveProgress = 1.f;
        
        for (auto& spr : getCurrDirection()) spr.setPosition(currPos);
        
        if (moveProgress == 1.f) {
            currPos = targetPos;
        }
    }
}


