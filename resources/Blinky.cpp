#include "Blinky.h"



int Blinky::manhattanDist(int x1, int y1, int x2, int y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

std::pair<Directions, sf::Vector2f> Blinky::shortesDirectiontoPacman(Map& map, const sf::Vector2f& pacmanPoss) {
    int ind_x = currPos.x / tile_x;
    int ind_y = currPos.y / tile_y;
    int pac_x = pacmanPoss.x / tile_x;
    int pac_y = pacmanPoss.y / tile_y;
    
    int minDist = std::numeric_limits<int>::max();
    Directions bestDirection = Directions::None; 
    // Define possible directions: up, down, left, right
    std::vector<std::pair<int, int>> dirs {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    sf::Vector2f targetPos;

    int i = 0;
    for (auto [dx, dy] : dirs) {
        ++i;
        int curr_dist = manhattanDist(dx + ind_x, dy + ind_y, pac_x, pac_y);

        if (isValidPosition({dx + ind_x, dy + ind_y}, map)) {
            if (curr_dist < minDist) {
                minDist = curr_dist;
                targetPos = currPos + sf::Vector2f(dx * tile_x, dy * tile_y);
                bestDirection = static_cast<Directions>(i - 1);
            }
        }
    }
    
    return {bestDirection, targetPos};
}

void Blinky::move(Map& map, Pacman& pac, float deltaTime) {
     if (moveProgress >= 1.f) {
        auto pacmanPoss = pac.getCurrPosition();
        auto targetInfo = shortesDirectiontoPacman(map, pacmanPoss);
        currDir = targetInfo.first;
        targetPos = targetInfo.second;

        moveProgress = 0.f;
    } 
    if (moveProgress < 1.f) {

        moveProgress += deltaTime / moveDuration;
        if (moveProgress > 1.f) moveProgress = 1.f;
        currPos = currPos + (targetPos - currPos) * (deltaTime / moveDuration);
        for (auto& spr : getCurrDirection()) spr.setPosition(currPos);

        
        if (moveProgress == 1.f) {
            currPos = targetPos;
        }
    }
}


