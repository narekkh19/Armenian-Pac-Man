#include "Pacman.h"
#include "Map.h"

Pacman::Pacman() : movementClock() {
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
    currPos = {1 * min_x, 1 * min_y};
    currDir = Directions::Right;
    for (auto& pacmans : getCurrDirection()) pacmans.setPosition(currPos);
}


Pacman::Pacman(const Pacman& other) :
    pacmanImage(other.pacmanImage),
    Upframes(other.Upframes),
    Rframes(other.Rframes),
    Dframes(other.Dframes),
    Lframes(other.Lframes),
    currPos(other.currPos),
    currDir(other.currDir) {}

Pacman& Pacman::operator= (const Pacman& other) {
    pacmanImage = other.pacmanImage;
    Upframes = other.Upframes;
    Rframes = other.Rframes;
    Dframes = other.Dframes;
    Lframes =  other.Lframes;
    currDir = other.currDir; 
    currPos = other.currPos;
    return *this;
}

sf::Vector2f Pacman::getCurrPosition() {
    return currPos;
}

void Pacman::setCurrPosition(int i, int j) {
    currPos = sf::Vector2f(j * min_x, i * min_y);
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
    int ind_x = nextPos.x / min_x;
    int ind_y = nextPos.y / min_y;

    if (ind_x >= 0 && ind_y >= 0 && ind_x < window_x && ind_y < window_y) {
        if (map.level[ind_y][ind_x] != static_cast<int>(MapDetails::Block)) {
            return true;
        }
    }
    return false;
}

void Pacman::eat(const sf::Vector2f& nextPos, Map& map) {
    int ind_x = nextPos.x / min_x;
    int ind_y = nextPos.y / min_y;
    map.level[ind_y][ind_x] = 0;
} 

void Pacman::PacmanMovement(sf::Event::KeyEvent currKey, Map& map) {
if (movementClock.getElapsedTime().asSeconds() > moveInterval) {
    auto& currSprite = getCurrDirection();
    if (currSprite.empty()) return;
    sf::Vector2f old_position = (currSprite)[0].getPosition(); //get Pac-mans current position
    sf::Vector2f new_position = old_position;
    bool moved {};

    switch (currKey.code) {
        case sf::Keyboard::Unknown:
            return;
        case sf::Keyboard::Up:
            moved = isValidPosition({new_position.x, new_position.y - min_y}, map);
                if (moved) {
                    new_position.y -= min_y;
                    currDir = Directions::Up;
                }
            break;

        case sf::Keyboard::Right:
            moved = isValidPosition({new_position.x + min_x, new_position.y}, map);
                if (moved) {
                    new_position.x += min_x;
                    currDir = Directions::Right;
                }
            break;
            
            
        case sf::Keyboard::Down:
            moved = isValidPosition({new_position.x, new_position.y + min_y}, map);
                if (moved) {
                    new_position.y += min_y;
                    currDir = Directions::Down;
                }
            break;
            
        case sf::Keyboard::Left:
            moved = isValidPosition({new_position.x - min_x, new_position.y}, map);
                if (moved) {
                    new_position.x -= min_x;
                    currDir = Directions::Left;
                }
            break;
            
        default: return;
    }
    
    if (moved) {
        eat(new_position, map); 
        currPos = std::move(new_position);
        for (auto& currSprite : getCurrDirection()) currSprite.setPosition(currPos);
    }
    movementClock.restart();
}
}


void Pacman::draw(sf::RenderWindow& window,  int pac_frameindex) {
    window.draw(getCurrDirection()[pac_frameindex]);
}
