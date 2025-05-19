#include "Ghost.h"
#include "../Map.h"
#include <iostream>


Ghost::Ghost(int i, int j, Ghosts type)  :   currPos(j * tile_x, i * tile_y), currDir(Directions::Up), startPos(currPos), targetPos() {
   
    if (!GhostImage.loadFromFile("images/whole.png")) {
        throw std::runtime_error("Failed to load ghost texture");
    }

    int col = static_cast<int>(type); // every color is in the particular columns 
    sf::Sprite Ghost_spr(GhostImage);
    
    
    for (int row = 0; row < Ghost_image_Directions; ++row) {
        Ghost_spr.setTextureRect(sf::IntRect(col * 50, row * 50, 50, 50));

        Ghost_spr.setScale(34.f / 50.f, 30.f / 50.f);

        if (row < 2) {
            Rframes.push_back(Ghost_spr);
        } else if (row < 4) {
            Dframes.push_back(Ghost_spr);
        } else if (row < 6) {
            Lframes.push_back(Ghost_spr);
        } else {
            Upframes.push_back(Ghost_spr);
        }
    }
    
    for (auto& currSprite : getCurrDirection()) currSprite.setPosition(currPos);
}

Ghost::Ghost(const Ghost& other) 
    :   type(other.type),
        Upframes(other.Upframes),
        Rframes(other.Rframes),
        Dframes(other.Dframes),
        Lframes(other.Lframes),
        currPos(other.currPos),
        currDir(other.currDir),
        startPos(other.startPos),
        targetPos(other.targetPos) {}

Ghost::Ghost(Ghost&& other) 
    :   type{std::move(other.type)},
        Upframes{std::move(other.Upframes)},
        Rframes{std::move(other.Rframes)},
        Dframes{std::move(other.Dframes)},
        Lframes{std::move(other.Lframes)},
        currPos{std::move(other.currPos)},
        currDir{std::move(other.currDir)},                            
        startPos{std::move(other.startPos)},
        targetPos{std::move(other.targetPos)} {}

Ghost& Ghost::operator=(const Ghost& other) {
    if (&other == this) return *this;
    type         = other.type;
    Upframes     = other.Upframes;
    Rframes      = other.Rframes;
    Dframes      = other.Dframes;
    Lframes      = other.Lframes;
    currPos      = other.currPos;
    currDir      = other.currDir;
    startPos     = other.startPos;
    targetPos    = other.targetPos;
    return *this;
}

Ghost& Ghost::operator=(Ghost&& other) {
    if (&other == this) return *this;
    type         = std::move(other.type);
    Upframes     = std::move(other.Upframes);
    Rframes      = std::move(other.Rframes);
    Dframes      = std::move(other.Dframes);
    Lframes      = std::move(other.Lframes);
    currPos      = std::move(other.currPos);
    currDir      = std::move(other.currDir);
    startPos     = std::move(other.startPos);
    targetPos    = std::move(other.targetPos);
    return *this;
}

std::vector<sf::Sprite>& Ghost::getCurrDirection() {
    switch(currDir) {
        case Directions::Right: return Rframes;
        case Directions::Down:  return Dframes;
        case Directions::Left:  return Lframes;
        case Directions::Up:    return Upframes;
        case Directions::None: break;
    }
    return Upframes;  // never happens, just to silence warnings
}

Directions Ghost::oppositeDir(Directions currDir) const {
    if (currDir == Directions::Left) return Directions::Right;
    if (currDir == Directions::Right) return Directions::Left;
    if (currDir == Directions::Up) return Directions::Down;
    return Directions::Up;
}



bool Ghost::isValidPosition(int ind_x, int ind_y, const Map& map) const {
    if (ind_x >= 0 && ind_y >= 0 && ind_x < window_x && ind_y < window_y) {
        if (!map.isBlock(map.level[ind_y][ind_x])) {
            return true;
        }
    }
    return false;
}

void Ghost::setCurrPosition(int i, int j) {
    currPos = sf::Vector2f(j * tile_x, i * tile_y);
}

void Ghost::setDontMove(bool b) {
    dontMove = true;
}

sf::Vector2f Ghost::getCurrPosition() {
    return currPos;
}

void Ghost::draw(sf::RenderWindow& window, int ghost_frameindex) {
    window.draw(getCurrDirection()[ghost_frameindex]);
}
