#include "Pacman.h"
#include "Map.h"
#include <iostream>
#include <thread>
#include <chrono>

Pacman::Pacman() :  currPos(tile_x * 1.0f, tile_y * 1.0f), // Start at top-left of tile (1,1)
                    currDir(Directions::Right),
                    startPos(currPos),
                    targetPos(currPos),
                    requestedDir(Directions::None),
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
    startPos(other.startPos),
    targetPos(other.targetPos),
    requestedDir(other.requestedDir),
    nextKey(other.nextKey)
    {}

Pacman& Pacman::operator= (const Pacman& other) {
    pacmanImage  = other.pacmanImage;
    Upframes     = other.Upframes;
    Rframes      = other.Rframes;
    Dframes      = other.Dframes;
    Lframes      =  other.Lframes;
    currDir      = other.currDir; 
    currPos      = other.currPos;
    startPos     = other.startPos,
    targetPos    = other.targetPos;
    requestedDir = other.requestedDir;
    nextKey      = other.nextKey;
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
            
        case Directions::None:
            break;
    }
    return Rframes;
}

bool Pacman::isValidPosition(const sf::Vector2f& nextPos, const Map& map) const {
    int ind_x = nextPos.x / tile_x;
    int ind_y = nextPos.y / tile_y;

    if (ind_x >= 0 && ind_y >= 0 && ind_x < window_x && ind_y < window_y) {
        if (!map.isBlock(map.level[ind_y][ind_x])) {
            return true;
        }
    }
    return false;
}

Directions Pacman::getcurrDir() {
    return currDir;
}

void Pacman::eat(const sf::Vector2f& nextPos, Map& map) {
    int ind_x = nextPos.x / tile_x;
    int ind_y = nextPos.y / tile_y;
    if (map.level[ind_y][ind_x] == 0) return;
    map.level[ind_y][ind_x] = 0;
    if (map.level[ind_y][ind_x] == static_cast<int>(GameIntities::MegaFood)) return;
    score += 1000;
} 


bool Pacman::lastWord(sf::RenderWindow& window) {
    static sf::Sprite curr_spr(pacmanImage);
    static std::vector<sf::Sprite> death_spr;
    [[maybe_unused]] static bool _ =  [this]() {
        for (int i = 0; i < 11; ++i) {
            curr_spr.setTextureRect(sf::IntRect(7 * 50, i * 50, 50, 50));
            curr_spr.setScale(34.f / 50.f, 30.f / 50.f);
            curr_spr.setPosition(currPos);            
            death_spr.push_back(curr_spr);        
        }
        return true;
    }();

    float frameTime = 0.10f;
    static sf::Clock clock;
    static sf::Time overalTime;
    static size_t currSpriteIndex = 0;    

    window.draw(death_spr[currSpriteIndex]);


    overalTime += clock.restart();
    
    
    if (overalTime.asSeconds() > frameTime) {
        ++currSpriteIndex;
        if (currSpriteIndex == death_spr.size()) {
            animationEnded = true;
            return false;
        }
        overalTime = sf::Time::Zero;
    }
    return true;
}

bool Pacman::winAnimation(sf::RenderWindow& window) {
    static std::vector<std::vector<sf::Sprite>*> AllSprites;

    [[maybe_unused]] static bool _ =  [this]() {
        AllSprites.push_back(&Rframes);
        AllSprites.push_back(&Dframes);
        AllSprites.push_back(&Lframes);
        AllSprites.push_back(&Upframes);
        for (std::vector<sf::Sprite>* currDirection : AllSprites) {
            for (sf::Sprite& currSprite : *currDirection) {
                currSprite.setPosition(currPos);
            }
        }
        return true;
    }();
    
    float frameTime = 0.15f;
    static sf::Clock clock;
    static sf::Time overalTime;
    static size_t currDirectionindex = 0;
    static size_t currSpriteIndex = 0;    


    window.draw((*(AllSprites[currDirectionindex]))[currSpriteIndex]);

    overalTime += clock.restart();
    
    
    if (overalTime.asSeconds() > frameTime) {
        ++currSpriteIndex;
        if (currSpriteIndex == (*(AllSprites[currDirectionindex])).size()) {
            ++currDirectionindex;
            currSpriteIndex = 0;
            if (currDirectionindex == AllSprites.size()) {
                animationEnded = true;
                return false;
            }
        } 
        overalTime = sf::Time::Zero;
    }
    return true;
}

void Pacman::PacmanMovement(sf::Event::KeyEvent currKey, Map& map, float deltaTime) {
    if (PacmanWin || PacmanDied) return;
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
        float progressDelta = deltaTime / moveDuration;
        moveProgress += progressDelta;
        currPos = startPos + (targetPos - startPos) * moveProgress;
        if (moveProgress > 1.f) moveProgress = 1.f;

        currPos = currPos + (targetPos - currPos) * (deltaTime / moveDuration);
        for (auto& spr : getCurrDirection()) spr.setPosition(currPos);

        // Finished movement → Eat
        if (moveProgress == 1.f) {
            eat(targetPos, map);
            currPos = targetPos;
            startPos = currPos;
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
            case Directions::None: break;
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

void Pacman::setWin(bool flag) {
    PacmanWin = true;
}

void Pacman::setDied(bool flag) {
    PacmanDied = true;
}

bool Pacman::draw(sf::RenderWindow& window,  int pac_frameindex) {
    if ((PacmanDied || PacmanWin) && animationEnded) return true;
    if (PacmanDied) {
        [[maybe_unused]] bool ret = lastWord(window);
        if (!ret) return true;
        return false;
    } else if (PacmanWin) {
        [[maybe_unused]] bool ret = winAnimation(window);
        if (!ret) return true;
        return false;
    }

    window.draw(getCurrDirection()[pac_frameindex]);
    return false;
}

int Pacman::getScore() {
    return score;
}

bool Pacman::hasWon() {
    return PacmanWin;
}

bool Pacman::isDead() {
    return PacmanDied;
}