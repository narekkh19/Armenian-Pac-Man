#include "Ghost.h"
#include "Map.h"
#include <iostream>

Ghost::Ghost(const Ghosts& _type, int i, int j) : type{_type}, gen(std::random_device{}()), dirs{{-1,0},{0,1},{1,0},{0,-1}} {
    GhostImage.loadFromFile("images/whole.png");
    sf::Sprite Ghost_spr(GhostImage);
    int row = static_cast<int>(type); // every color is in the particular columns 

    for (int i = 0; i < Ghost_image_Directions; ++i) {
        Ghost_spr.setTextureRect(sf::IntRect(row * 50, i * 50, 50, 50));
        Ghost_spr.setScale(34.f / 50.f, 30.f / 50.f);

        if (i < 2) {
            Rframes.push_back(Ghost_spr);
        } else if (i < 4) {
            Dframes.push_back(Ghost_spr);
        } else if (i < 6) {
            Lframes.push_back(Ghost_spr);
        } else {
            Upframes.push_back(Ghost_spr);
        }
    }
    currPos = sf::Vector2f(j * min_x, i * min_y);
    currDir = Directions::Up;
    for (auto& currSprite : getCurrDirection()) currSprite.setPosition(currPos);
}

std::vector<sf::Sprite>& Ghost::getCurrDirection() {
    switch(currDir) {
        case Directions::Right: return Rframes;
        case Directions::Down:  return Dframes;
        case Directions::Left:  return Lframes;
        case Directions::Up:    return Upframes;
      }
      return Upframes;  // never happens, just to silence warnings
}

bool Ghost::isValidPosition(const sf::Vector2f& nextPos, const Map& map) const {
    int ind_x = nextPos.x / min_x;
    int ind_y = nextPos.y / min_y;
    if (ind_x >= 0 && ind_y >= 0 && ind_x < window_x && ind_y < window_y) {
        if (map.level[ind_y][ind_x] != static_cast<int>(MapDetails::Block)) {
            return true;
        }
    }
    return false;
}

void Ghost::GhostMovement(Map& map) {
    auto& currSprite = getCurrDirection();
    if (currSprite.empty()) return;  

    std::shuffle(dirs.begin(), dirs.end(), gen);
    int i = 0; // for Directions (Up, Right ...)
    for (auto [dx,dy] : dirs) {
        ++i;
        sf::Vector2f test = currPos + sf::Vector2f(dx * min_x, dy * min_y);
        if (!isValidPosition(test, map)) continue;
        
        currPos = std::move(test);
        currDir = static_cast<Directions>(i - 1);

        for (auto& currSprite : getCurrDirection()) {
            currSprite.setPosition(currPos);
        }
        break;
    }
}

void Ghost::setCurrPosition(int i, int j) {
    currPos = sf::Vector2f(j * min_x, i * min_y);
}


sf::Vector2f Ghost::getCurrPosition() {
    return currPos;
}

Ghost::Ghost(const Ghost& other) 
    :   type(other.type),
        GhostImage(other.GhostImage),
        Rframes(other.Rframes),
        Dframes(other.Dframes),
        Lframes(other.Lframes),
        Upframes(other.Upframes),
        currPos(other.currPos),
        currDir(other.currDir) {}

Ghost& Ghost::operator=(const Ghost& other) {
    if (&other == this) return *this;
    type         = other.type;
    GhostImage   = other.GhostImage;
    Rframes      = other.Rframes;
    Dframes      = other.Dframes;
    Lframes      = other.Lframes;
    Upframes     = other.Upframes;
    currPos      = other.currPos;
    currDir      = other.currDir;
    return *this;
}

void Ghost::draw(sf::RenderWindow& window, int ghost_frameindex) {
    window.draw(getCurrDirection()[ghost_frameindex]);
}
