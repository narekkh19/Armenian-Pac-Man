#ifndef TUFIBLOCK_H
#define TUFIBLOCK_H

#include "SFML/Graphics.hpp"
#include "GameElements.h"

class Block {
    sf::Texture TufiBlockImage;
    sf::Sprite tuf_spr;
    
    sf::Texture HraparakImage;
    sf::Sprite hr_spr;

public:

    Block();
    void draw(sf::RenderWindow& window, GameIntities which, int i, int j);
    // sf::Sprite& getBlock(GameIntities which);

};


#endif //TUFIBLOCK_H