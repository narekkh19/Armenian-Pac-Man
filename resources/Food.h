#ifndef FOOD_H
#define FOOD_H

#include "SFML/Graphics.hpp"
#include "GameElements.h"


class Food {
    sf::Texture DramImage;
    sf::Sprite dram_spr;

    sf::Texture XorovImage;
    sf::Sprite xorov_spr;

    public:
        Food();
        void draw(sf::RenderWindow& window, GameIntities type, int i, int j);
};

#endif //FOOD_H