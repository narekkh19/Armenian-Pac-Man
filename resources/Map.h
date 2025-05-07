#ifndef MAP_H
#define MAP_H

#include "Ghost.h"
#include "TufiBlock.h"
#include "Dram.h"
#include "Pacman.h"
#include <vector>
#include "SFML/Graphics.hpp"
#include "GameElements.h"

class Map {
    std::vector<std::vector<int>> level;
    Pacman pac;
    TufiBlock tuf;
    std::vector<Ghost> hresh;
    Dram hazarnoc;
    friend Pacman;
    friend Ghost;
public:
        Map() : pac(), tuf(), hresh{Ghost(Ghosts::Red, 11, 19), Ghost(Ghosts::Orange, 11, 20), Ghost(Ghosts::Green, 11, 21)}, hazarnoc() {}       

        void loadLevel();
        Pacman& getPacman();
        TufiBlock& getTufiBlock();
        Dram& getDram();
        std::vector<Ghost>& getGhost();
        void draw(sf::RenderWindow& window);
};      

#endif //MAP_H