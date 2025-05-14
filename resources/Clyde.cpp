#include "Clyde.h"
#include <iostream>

int Clyde::manhattanDist(int x1, int y1, int x2, int y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}



std::pair<Directions, sf::Vector2f> Clyde::ClydeHesitating(Map& map, Pacman& pac) {
    int ind_x = currPos.x / tile_x;
    int ind_y = currPos.y / tile_y;
    
    auto pacmanPos = pac.getCurrPosition();
    auto clydePos = getCurrPosition();

    float dist_x = pacmanPos.x - clydePos.x;
    float dist_y = pacmanPos.y - clydePos.y;
    float dist = std::sqrt(dist_x * dist_x + dist_y * dist_y); //Pythagoras theorem
    
    sf::Vector2f DesiredPos {};
    sf::Vector2f BottomRightCorner (tile_x * (window_x - 2), tile_y * (window_y - 2));

    if (dist >= 8)
        DesiredPos = pacmanPos;
    else
        DesiredPos = BottomRightCorner;
    
    int minDist = std::numeric_limits<int>::max();
    Directions bestDirection = Directions::None; 

    int des_x = DesiredPos.x / tile_x;
    int des_y = DesiredPos.y / tile_y;

    // Define possible directions: up, down, left, right
    std::vector<std::pair<int, int>> dirs {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    sf::Vector2f targetPos;

    int i = 0;
    for (auto [dx, dy] : dirs) {
        ++i;
        int curr_dist = manhattanDist(dx + ind_x, dy + ind_y, des_x, des_y);

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


void Clyde::move(Map& map, Pacman& pac, float deltaTime) {
    
    if (moveProgress >= 1.f) {
        auto targetInfo = ClydeHesitating(map, pac);
        currDir = targetInfo.first;
        startPos = currPos;        
        targetPos = targetInfo.second;

        moveProgress = 0.f;
        for (auto& spr : getCurrDirection()) spr.setPosition(currPos);

        
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


