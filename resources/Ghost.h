#ifndef GHOST_H
#define GHOST_H

#include "SFML/Graphics.hpp"
#include "Pacman.h"
#include <algorithm>
#include <random>
#include <vector>
#include "GameElements.h"
#include "Blinky.h"

class Map;
class Blinky;
class Pinky;
class Inky;
class Clyde;

class Ghost {
    Ghosts type;
    static sf::Texture GhostImage;
    std::vector<sf::Sprite> Rframes;
    std::vector<sf::Sprite> Dframes; 
    std::vector<sf::Sprite> Lframes; 
    std::vector<sf::Sprite> Upframes;
    sf::Vector2f currPos;
    Directions currDir;
    std::mt19937 gen;                    
    std::vector<std::pair<int,int>> dirs;
    sf::Vector2f targetPos;      // the tile‐center we’re sliding toward
    float   moveProgress = 1.f;  // 0→1 progress of slide (1 means “arrived”)
    float   moveDuration = 0.2f; 
    static constexpr int Ghost_image_Directions = 8;
    
    friend class Blinky;
    friend class Pinky;
    friend class Inky;
    friend class Clyde;

    
    public:
        Ghost(int i, int j);
        Ghost() = delete;
        Ghost(const Ghost& other);
        Ghost(Ghost&& other);
        Ghost& operator=(const Ghost& other);
        Ghost& operator=(Ghost&& other);
            
        std::vector<sf::Sprite>& getCurrDirection();
        virtual void move (Map& map, Pacman& pac, float deltaTime) = 0;
        bool isValidPosition(const sf::Vector2f& nextPos, const Map& map) const;
        void setCurrPosition(int i, int j);
        sf::Vector2f getCurrPosition();
        void draw(sf::RenderWindow& window, int ghost_frameindex);
        
};

#endif //GHOST_H