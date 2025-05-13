#include "Ghost.h"
#include "Map.h"
#include <iostream>

sf::Texture Ghost::GhostImage;

Ghost::Ghost(int i, int j)  :                       currPos(j * tile_x, i * tile_y),
                                                    currDir(Directions::Up),
                                                    gen(std::random_device{}()),
                                                    dirs{{0,-1}, {1,0}, {0,1}, {-1,0}},
                                                    targetPos()
{
    static bool loaded = [] {
        if (!GhostImage.loadFromFile("images/whole.png")) {
            throw std::runtime_error("Failed to load ghost texture");
        }
        return true;
    }();
    sf::Sprite Ghost_spr(GhostImage);
    int col = static_cast<int>(type); // every color is in the particular columns 
    sf::Sprite test;
    

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
        Rframes(other.Rframes),
        Dframes(other.Dframes),
        Lframes(other.Lframes),
        Upframes(other.Upframes),
        currPos(other.currPos),
        currDir(other.currDir),
        gen(other.gen),
        dirs(other.dirs),
        targetPos(other.targetPos) {}

Ghost::Ghost(Ghost&& other) 
    :   type{std::move(other.type)},
        Upframes{std::move(other.Upframes)},
        Rframes{std::move(other.Rframes)},
        Dframes{std::move(other.Dframes)},
        Lframes{std::move(other.Lframes)},
        currPos{std::move(other.currPos)},
        currDir{std::move(other.currDir)},                            
        gen{std::move(other.gen)},
        dirs{std::move(other.dirs)},
        targetPos{std::move(other.targetPos)} {}

Ghost& Ghost::operator=(const Ghost& other) {
    if (&other == this) return *this;
    type         = other.type;
    Rframes      = other.Rframes;
    Dframes      = other.Dframes;
    Lframes      = other.Lframes;
    Upframes     = other.Upframes;
    currPos      = other.currPos;
    currDir      = other.currDir;
    gen          = other.gen;
    dirs         = other.dirs;
    targetPos    = other.targetPos;
    return *this;
}

Ghost& Ghost::operator=(Ghost&& other) {
    if (&other == this) return *this;
    type         = std::move(other.type);
    Rframes      = std::move(other.Rframes);
    Dframes      = std::move(other.Dframes);
    Lframes      = std::move(other.Lframes);
    Upframes     = std::move(other.Upframes);
    currPos      = std::move(other.currPos);
    currDir      = std::move(other.currDir);
    gen          = std::move(other.gen);
    dirs         = std::move(other.dirs);
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


bool Ghost::isValidPosition(const sf::Vector2f& nextPos, const Map& map) const {
    int ind_x = nextPos.x / tile_x;
    int ind_y = nextPos.y / tile_y;
    if (ind_x >= 0 && ind_y >= 0 && ind_x < window_x && ind_y < window_y) {
        if (map.level[ind_y][ind_x] != static_cast<int>(MapDetails::Block)) {
            return true;
        }
    }
    return false;
}

void Ghost::setCurrPosition(int i, int j) {
    currPos = sf::Vector2f(j * tile_x, i * tile_y);
}


sf::Vector2f Ghost::getCurrPosition() {
    return currPos;
}

void Ghost::draw(sf::RenderWindow& window, int ghost_frameindex) {
    window.draw(getCurrDirection()[ghost_frameindex]);
}
