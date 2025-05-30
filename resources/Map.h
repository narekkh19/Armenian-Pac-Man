#ifndef MAP_H
#define MAP_H

#include "Ghost/Ghost.h"
#include "Block.h"
#include "Food.h"
#include "Pacman.h"
#include "Font.h"
#include <vector>
#include "SFML/Graphics.hpp"
#include "GameElements.h"

class Map {
    std::vector<std::vector<int>> level;
    Pacman pac;
    Block block;
    Food meal;
    std::vector<Ghost*> hresh;
    Font pacmanScore;
    friend Pacman;
    friend Ghost;
    
    sf::Font endGameFont;
    sf::Text endGameMessageText;
    
    public:
        Map();
        ~Map();
        void loadLevel();
        Pacman& getPacman();
        Block& getBlock();
        Food& getDram();
        bool isBlock(const int i) const;
        std::vector<Ghost*>& getGhost();
        void checkGameResult(sf::RenderWindow& window);
        void draw(sf::RenderWindow& window);
};      

#endif //MAP_H