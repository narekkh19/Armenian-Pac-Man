#include "Inky.h"
#include <iostream>


int Inky::manhattanDist(int x1, int y1, int x2, int y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}


std::pair<int, int> Inky::manhattanDistCoord(int x1, int y1, int x2, int y2) {
    return {std::abs(x1 - x2), std::abs(y1 - y2)};
}

std::pair<Directions, sf::Vector2f> Inky::InkysUnpredictableLogic(Map& map, Pacman& pac) {
    int ind_x = static_cast<int>(currPos.x) / tile_x;
    int ind_y = static_cast<int>(currPos.y) / tile_y;

    auto pacmanPos = pac.getCurrPosition();
    int pac_x = pacmanPos.x / tile_x;
    int pac_y = pacmanPos.y / tile_y;

    auto [dx, dy] = manhattanDistCoord(ind_x, ind_y, pac_x, pac_y);
    sf::Vector2f desiredPos = sf::Vector2f((ind_x + 2 * dx) * tile_x, (ind_y + 2 * dy) * tile_y);

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



void Inky::move(Map& map, Pacman& pac, float deltaTime) {

     if (moveProgress >= 1.f) {
        auto targetInfo = InkysUnpredictableLogic(map, pac);
        currDir = targetInfo.first;
        startPos = currPos;
        targetPos = targetInfo.second;

        moveProgress = 0.f;
        
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


