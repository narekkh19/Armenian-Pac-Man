#include "Blinky.h"
#include <iostream>


int Blinky::manhattanDist(int x1, int y1, int x2, int y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}std::pair<Directions, sf::Vector2f> Blinky::shortestDirectiontoPacman(Map& map, const sf::Vector2f& pacmanPos) {
    int ind_x = static_cast<int>(currPos.x) / tile_x;
    int ind_y = static_cast<int>(currPos.y) / tile_y;

    int pac_x = static_cast<int>(pacmanPos.x) / tile_x;
    int pac_y = static_cast<int>(pacmanPos.y) / tile_y;

    int minDist = std::numeric_limits<int>::max();
    Directions bestDirection = Directions::None;
    sf::Vector2f resultingTargetPixelPos(static_cast<float>(ind_x * tile_x), static_cast<float>(ind_y * tile_y));

    std::vector<std::pair<int, int>> dirs_tile_offsets = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    std::vector<Directions> dirEnums = {Directions::Left, Directions::Right, Directions::Up, Directions::Down};

    // First try avoiding reverse direction
    for (size_t i = 0; i < dirs_tile_offsets.size(); ++i) {
        auto [dtx, dty] = dirs_tile_offsets[i];
        Directions dir = dirEnums[i];

        if (dir == oppositeDir(currDir))
            continue;

        int next_x = ind_x + dtx;
        int next_y = ind_y + dty;

        if (isValidPosition(next_x, next_y, map)) {
            int dist = manhattanDist(next_x, next_y, pac_x, pac_y);
            if (dist < minDist) {
                minDist = dist;
                bestDirection = dir;
                resultingTargetPixelPos = sf::Vector2f(next_x * tile_x, next_y * tile_y);
            }
        }
    }

    // If all directions are reverse (dead-end or box), allow reversing
    if (bestDirection == Directions::None) {
        for (size_t i = 0; i < dirs_tile_offsets.size(); ++i) {
            auto [dtx, dty] = dirs_tile_offsets[i];
            Directions dir = dirEnums[i];

            int next_x = ind_x + dtx;
            int next_y = ind_y + dty;

            if (isValidPosition(next_x, next_y, map)) {
                int dist = manhattanDist(next_x, next_y, pac_x, pac_y);
                if (dist < minDist) {
                    minDist = dist;
                    bestDirection = dir;
                    resultingTargetPixelPos = sf::Vector2f(next_x * tile_x, next_y * tile_y);
                }
            }
        }
    }

    return {bestDirection, resultingTargetPixelPos};
}


void Blinky::move(Map& map, Pacman& pac, float deltaTime) {
    if (dontMove) return;
     if (moveProgress >= 1.f) {
        auto pacmanPos = pac.getCurrPosition();
        auto targetInfo = shortestDirectiontoPacman(map, pacmanPos);
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


