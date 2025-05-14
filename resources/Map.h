#ifndef MAP_H
#define MAP_H

#include "Ghost/Ghost.h"
#include "Block.h"
#include "Dram.h"
#include "Pacman.h"
#include <vector>
#include "SFML/Graphics.hpp"
#include "GameElements.h"

class Map {
    std::vector<std::vector<int>> level;
    Pacman pac;
    Block block;
    std::vector<Ghost*> hresh;
    Dram hazarnoc;
    friend Pacman;
    friend Ghost;
public:
        Map();
        void loadLevel();
        Pacman& getPacman();
        Block& getBlock();
        Dram& getDram();
        bool isBlock(const int i) const;
        std::vector<Ghost*>& getGhost();
        void checkGameResult(sf::RenderWindow& window);
        void draw(sf::RenderWindow& window);
};      

#endif //MAP_H