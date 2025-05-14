#include "Pinky.h"
#include <iostream>

int Pinky::manhattanDist(int x1, int y1, int x2, int y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}
std::pair<Directions, sf::Vector2f> Pinky::DirectionAheadPacman(Map& map, Pacman& pac) {
    int ind_x = static_cast<int>(currPos.x) / tile_x;
    int ind_y = static_cast<int>(currPos.y) / tile_y;

    auto pacmanPos = pac.getCurrPosition();
    auto tileOffset = DirectionToCoord(pac.getcurrDir());
    sf::Vector2f desiredPos = pacmanPos + sf::Vector2f(4 * tileOffset.first * tile_x, 4 * tileOffset.second * tile_y);

    int des_x = desiredPos.x / tile_x;
    int des_y = desiredPos.y / tile_y;

    int minDist = std::numeric_limits<int>::max();
    Directions bestDirection = Directions::None;
    sf::Vector2f resultingTargetPixelPos(static_cast<float>(ind_x * tile_x), static_cast<float>(ind_y * tile_y));

    std::vector<std::pair<int, int>> dirs_tile_offsets = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    std::vector<Directions> dirEnums = {Directions::Left, Directions::Right, Directions::Up, Directions::Down};

    for (size_t i = 0; i < dirs_tile_offsets.size(); ++i) {
        auto [dx, dy] = dirs_tile_offsets[i];
        int nx = ind_x + dx;
        int ny = ind_y + dy;

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


