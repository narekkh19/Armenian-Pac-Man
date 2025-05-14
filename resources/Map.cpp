#include "Map.h"
#include "Ghost/Blinky.h"
#include "Ghost/Pinky.h"
#include "Ghost/Inky.h"
#include "Ghost/Clyde.h"
#include <cmath>

Map::Map() : pac(), block(), hresh{}, hazarnoc() {
    hresh.push_back(new Blinky(11, 19));
    hresh.push_back(new Pinky(11, 20));
    hresh.push_back(new Inky(11, 21));
    hresh.push_back(new Clyde(11, 22));
}


void Map::loadLevel() {
level = {
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}, // Row 0
    {2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2}, // Row 1
    {2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2}, // Row 2
    {2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2}, // Row 3
    {2,4,5,5,5,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2}, // Row 4
    {2,4,3,3,3,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2}, // Row 5
    {2,4,3,3,3,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2}, // Row 6
    {2,4,3,3,3,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2}, // Row 7
    {2,4,3,3,3,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2}, // Row 8
    {2,4,3,3,3,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2}, // Row 9
    {2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2}, // Row 10
    {2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2}, // Row 11
    {2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2}, // Row 12
    {2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2}, // Row 13
    {2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2}, // Row 14
    {2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2}, // Row 15
    {2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2}, // Row 16
    {2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2}, // Row 17
    {2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2}, // Row 18
    {2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2}, // Row 19
    {2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2}, // Row 20
    {2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2}, // Row 21
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}  // Row 22
};
}

Pacman& Map::getPacman() {
    return pac;
}

Block& Map::getBlock() {
    return block;
}

Dram& Map::getDram() {
    return hazarnoc;
}

bool Map::isBlock(const int i) const {
    if (i != static_cast<int>(GameIntities::Tuf)) {
        if (i != static_cast<int>(GameIntities::KesTuf)) {
            if (i != static_cast<int>(GameIntities::RedRoof)) {
                return false;
            }
        }
    } 
    return true;
}


std::vector<Ghost*>& Map::getGhost() {
    return hresh;
}

void Map::draw(sf::RenderWindow& window) {
    for (size_t i = 0; i < level.size(); ++i) {
        for (size_t j = 0; j < level[i].size(); ++j) {
            if (level[i][j] == 2) { 
                block.draw(window, GameIntities::Tuf, i, j);
            }
            else if (level[i][j] == 3) { 
                hazarnoc.drawDram(window, i, j);
            }
            else if (level[i][j] == 4) {
                block.draw(window, GameIntities::KesTuf, i, j);
            }
            else if (level[i][j] == 5) {
                block.draw(window, GameIntities::RedRoof, i, j);
            }
        }
    }
    
}

void Map::checkGameResult(sf::RenderWindow& window) {
    sf::Vector2f pacmanPos = getPacman().getCurrPosition();
    for (auto* ghost : getGhost()) {
        sf::Vector2f ghostPos = ghost->getCurrPosition();
        sf::Vector2f result = pacmanPos - ghostPos;
        if (std::fabs(result.x) < tile_x / 3 && std::fabs(result.y) < tile_y / 3) {
            // window.close();
        }
    }
}
