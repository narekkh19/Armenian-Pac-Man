#ifndef GHOST_H
#define GHOST_H

#include "SFML/Graphics.hpp"
#include "Pacman.h"
#include <algorithm>
#include <random>
#include <vector>
#include "GameElements.h"

class Map;

class Ghost {
    Ghosts type;
    sf::Texture GhostImage;
    std::vector<sf::Sprite> Rframes;
    std::vector<sf::Sprite> Dframes; 
    std::vector<sf::Sprite> Lframes; 
    std::vector<sf::Sprite> Upframes;
    sf::Vector2f currPos;
    Directions currDir;
    std::mt19937 gen;                    
    std::vector<std::pair<int,int>> dirs;
    static constexpr int Ghost_image_Directions = 8;
    
    
    public:
        Ghost(const Ghosts& _type, int i, int j);
        Ghost() = delete;
        Ghost(const Ghost& other);
        Ghost& operator=(const Ghost& o);

        std::vector<sf::Sprite>& getGhostSpriteByDirection(Directions currDir);
        std::vector<sf::Sprite>& getCurrDirection();
        void GhostMovement(Map& map);
        bool isValidPosition(const sf::Vector2f& nextPos, const Map& map) const;
        void setCurrPosition(int i, int j);
        sf::Vector2f getCurrPosition();
        void draw(sf::RenderWindow& window, int ghost_frameindex);
};

#endif //GHOST_H