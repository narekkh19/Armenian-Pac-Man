#include "Pinky.h"
#include <iostream>

int Pinky::manhattanDist(int x1, int y1, int x2, int y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

std::pair<Directions, sf::Vector2f> Pinky::DirectionAheadPacman(Map& map, Pacman& pac) {
    int ind_x = static_cast<int>(currPos.x) / tile_x;
    int ind_y = static_cast<int>(currPos.y) / tile_y;

    auto pacmanPos = pac.getCurrPosition();
    auto tilePos = DirectionToCoord(pac.getcurrDir());   
    sf::Vector2f DesiredPos = {pacmanPos.x + 4 * tilePos.first * tile_x, pacmanPos.y + 4 * tilePos.second * tile_y};

    int des_x = DesiredPos.x / tile_x;
    int des_y = DesiredPos.y / tile_y;

    int minDist = std::numeric_limits<int>::max();
    Directions bestDirection = Directions::None; 

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

std::pair<int, int> Pinky::DirectionToCoord(Directions dir) {
    if (dir == Directions::Up) return {-1, 0};
    if (dir == Directions::Right) return {1, 0};
    if (dir ==  Directions::Down) return {0, -1};
    return {0, 1};
}

void Pinky::move(Map& map, Pacman& pac, float deltaTime) {

     if (moveProgress >= 1.f) {
        auto targetInfo = DirectionAheadPacman(map, pac);
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


