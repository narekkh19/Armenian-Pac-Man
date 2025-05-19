#include "Clyde.h"
#include <iostream>

int Clyde::manhattanDist(int x1, int y1, int x2, int y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

std::pair<Directions, sf::Vector2f> Clyde::ClydeHesitating(Map& map, Pacman& pac) {
    int ind_x = static_cast<int>(currPos.x) / tile_x;
    int ind_y = static_cast<int>(currPos.y) / tile_y;

    auto pacmanPos = pac.getCurrPosition();
    auto clydePos = getCurrPosition();

    float dist_x = pacmanPos.x - clydePos.x;
    float dist_y = pacmanPos.y - clydePos.y;
    float dist = std::sqrt(dist_x * dist_x + dist_y * dist_y);

    sf::Vector2f desiredPos;
    if (dist >= 8 * tile_x) // 8 tiles in pixels
        desiredPos = pacmanPos;
    else
        desiredPos = sf::Vector2f((window_x - 2) * tile_x, (window_y - 2) * tile_y);

    int des_x = desiredPos.x / tile_x;
    int des_y = desiredPos.y / tile_y;

    int minDist = std::numeric_limits<int>::max();
    Directions bestDirection = Directions::None;
    sf::Vector2f resultingTargetPixelPos(static_cast<float>(ind_x * tile_x), static_cast<float>(ind_y * tile_y));

    std::vector<std::pair<int, int>> dirs_tile_offsets = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    std::vector<Directions> dirEnums = {Directions::Left, Directions::Right, Directions::Up, Directions::Down};

    for (size_t i = 0; i < dirs_tile_offsets.size(); ++i) {
        auto [dtx, dty] = dirs_tile_offsets[i];
        int nx = ind_x + dtx;
        int ny = ind_y + dty;

        if (isValidPosition(nx, ny, map) && dirEnums[i] != oppositeDir(currDir)) {
            int dist = manhattanDist(nx, ny, des_x, des_y);
            if (dist < minDist) {
                minDist = dist;
                bestDirection = dirEnums[i];
                resultingTargetPixelPos = sf::Vector2f(nx * tile_x, ny * tile_y);
            }
        }
    }

    return {bestDirection, resultingTargetPixelPos};
}


void Clyde::move(Map& map, Pacman& pac, float deltaTime) {
    if (dontMove) return;
    
    if (moveProgress >= 1.f) {
        auto targetInfo = ClydeHesitating(map, pac);
        currDir = targetInfo.first;
        startPos = currPos;        
        targetPos = targetInfo.second;

        moveProgress = 0.f;
        for (auto& spr : getCurrDirection()) spr.setPosition(currPos);

        
    } 
    if (moveProgress < 1.f) {
        static int i = 0;
        if (i == 2) {
            float progressDelta = deltaTime / moveDuration;
            moveProgress += progressDelta;
            currPos = startPos + (targetPos - startPos) * moveProgress;
            if (moveProgress > 1.f) moveProgress = 1.f;
            i = 0;
        }
        ++i;
        
        for (auto& spr : getCurrDirection()) spr.setPosition(currPos);
        
        if (moveProgress == 1.f) {
            currPos = targetPos;
        }
    }
}


