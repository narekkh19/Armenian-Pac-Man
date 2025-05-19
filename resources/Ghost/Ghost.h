#ifndef GHOST_H
#define GHOST_H

#include "SFML/Graphics.hpp"
#include "../Pacman.h"
#include <algorithm>
#include <random>
#include <vector>
#include "../GameElements.h"

class Map;
class Blinky;
class Pinky;
class Inky;
class Clyde;

class Ghost {
    Ghosts type;
    sf::Texture GhostImage;
    std::vector<sf::Sprite> Upframes;
    std::vector<sf::Sprite> Rframes;
    std::vector<sf::Sprite> Dframes; 
    std::vector<sf::Sprite> Lframes; 
    sf::Vector2f currPos;
    Directions currDir;
    sf::Vector2f startPos;  // NEW: Needed for smooth linear movement
    sf::Vector2f targetPos;      // the tile‐center we’re sliding toward
    float   moveProgress = 1.f;  // 0→1 progress of slide (1 means “arrived”)
    float   moveDuration = 0.2f; 
    bool dontMove = false; // when ghost eats pacman and pacman animation
    static constexpr int Ghost_image_Directions = 8;
    
    friend class Blinky;
    friend class Pinky;
    friend class Inky;
    friend class Clyde;

    
    public:
        Ghost(int i, int j, Ghosts type);
        Ghost() = delete;
        Ghost(const Ghost& other);
        Ghost(Ghost&& other);
        Ghost& operator=(const Ghost& other);
        Ghost& operator=(Ghost&& other);
            
        std::vector<sf::Sprite>& getCurrDirection();
        virtual void move (Map& map, Pacman& pac, float deltaTime) = 0;
        Directions oppositeDir(Directions currDir) const;
        void setDontMove(bool b);
        bool isValidPosition(int ind_x, int ind_y, const Map& map) const;
        void setCurrPosition(int i, int j);
        sf::Vector2f getCurrPosition();
        void draw(sf::RenderWindow& window, int ghost_frameindex);
        
};

#endif //GHOST_H