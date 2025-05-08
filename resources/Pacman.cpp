#include "Pacman.h"
#include "Map.h"
#include <iostream>

Pacman::Pacman() :  currPos(tile_x * 1.0f, tile_y * 1.0f), // Start at top-left of tile (1,1)
                    currDir(Directions::Right),
                    requestedDir(Directions::None),
                    targetPos(currPos),
                    nextKey(sf::Keyboard::Unknown)
{
    pacmanImage.loadFromFile("images/whole.png");

    sf::Sprite pacman_spr(pacmanImage);


    for (int i = 0; i < Pacman_Directions; ++i) {
        pacman_spr.setTextureRect(sf::IntRect(17 * 50, i * 50, 50, 50));
        pacman_spr.setScale(34.f / 50.f, 30.f / 50.f);
        if (i < 3) {
            Rframes.push_back(pacman_spr);
        } else if (i < 6) {
            Dframes.push_back(pacman_spr);
        } else if (i < 9) {
            Lframes.push_back(pacman_spr);
        } else {
            Upframes.push_back(pacman_spr);
        }
    }
    for (auto& pacmans : getCurrDirection()) pacmans.setPosition(currPos);
}


Pacman::Pacman(const Pacman& other) :
    pacmanImage(other.pacmanImage),
    Upframes(other.Upframes),
    Rframes(other.Rframes),
    Dframes(other.Dframes),
    Lframes(other.Lframes),
    currPos(other.currPos),
    currDir(other.currDir),
    requestedDir(other.requestedDir),
    targetPos(other.targetPos),
    nextKey(other.nextKey)
    {}

Pacman& Pacman::operator= (const Pacman& other) {
    pacmanImage = other.pacmanImage;
    Upframes = other.Upframes;
    Rframes = other.Rframes;
    Dframes = other.Dframes;
    Lframes =  other.Lframes;
    currDir = other.currDir; 
    currPos = other.currPos;
    requestedDir = other.requestedDir;
    targetPos = other.targetPos;
    nextKey = other.nextKey;
    return *this;
}

sf::Vector2f Pacman::getCurrPosition() {
    return currPos;
}

void Pacman::setCurrPosition(int i, int j) {
    currPos = sf::Vector2f(j * tile_x, i * tile_y);
}


std::vector<sf::Sprite>& Pacman::getCurrDirection() {
    switch (currDir) {
        case Directions::Right:
            return Rframes;
            
        case Directions::Down:
            return Dframes;
            
        case Directions::Left:
            return Lframes;
        
        case Directions::Up:
            return Upframes;
    }
    return Rframes;
}

bool Pacman::isValidPosition(const sf::Vector2f& nextPos, const Map& map) const {
    int ind_x = nextPos.x / tile_x;
    int ind_y = nextPos.y / tile_y;

    if (ind_x >= 0 && ind_y >= 0 && ind_x < window_x && ind_y < window_y) {
        if (map.level[ind_y][ind_x] != static_cast<int>(MapDetails::Block)) {
            return true;
        }
    }
    return false;
}

void Pacman::eat(const sf::Vector2f& nextPos, Map& map) {
    int ind_x = nextPos.x / tile_x;
    int ind_y = nextPos.y / tile_y;
    map.level[ind_y][ind_x] = 0;
} 

void Pacman::PacmanMovement(sf::Event::KeyEvent currKey, Map& map, float deltaTime) {
    // Buffer the key until we can act on it
    if (currKey.code != sf::Keyboard::Unknown)
        nextKey = currKey.code;

    // Only update requestedDir once per key press
    if (nextKey != sf::Keyboard::Unknown) {
        switch (nextKey) {
            case sf::Keyboard::Up:    requestedDir = Directions::Up;    break;
            case sf::Keyboard::Right: requestedDir = Directions::Right; break;
            case sf::Keyboard::Down:  requestedDir = Directions::Down;  break;
            case sf::Keyboard::Left:  requestedDir = Directions::Left;  break;
            default: break;
        }
    }

    // Move animation if in progress
    if (moveProgress < 1.f) {
        moveProgress += deltaTime / moveDuration;
        if (moveProgress > 1.f) moveProgress = 1.f;

        currPos = currPos + (targetPos - currPos) * (deltaTime / moveDuration);
        for (auto& spr : getCurrDirection()) spr.setPosition(currPos);

        // Finished movement → Eat
        if (moveProgress == 1.f) {
            eat(targetPos, map);
            currPos = targetPos;
        }

        return;
    }

    // Not moving: try to initiate new movement
    auto tryMove = [&](Directions dir) -> bool {
        sf::Vector2f offset;
        switch (dir) {
            case Directions::Up:    offset = {0, -tile_y}; break;
            case Directions::Right: offset = {tile_x, 0};  break;
            case Directions::Down:  offset = {0, tile_y};  break;
            case Directions::Left:  offset = {-tile_x, 0}; break;
            case Directions::None break;
        }

        sf::Vector2f nextPos = currPos + offset;
        if (isValidPosition(nextPos, map)) {
            currDir = dir;
            targetPos = nextPos;
            moveProgress = 0.f;
            nextKey = sf::Keyboard::Unknown; // reset buffer once used
            return true;
        }
        return false;
    };

    // Try to move in requestedDir (if different from currDir)
    if (!tryMove(requestedDir)) {
        // If can't move in requested, try current
        tryMove(currDir);
    }

    // Ensure sprite stays aligned
    for (auto& spr : getCurrDirection()) spr.setPosition(currPos);
}

void Pacman::draw(sf::RenderWindow& window,  int pac_frameindex) {
    window.draw(getCurrDirection()[pac_frameindex]);
}
