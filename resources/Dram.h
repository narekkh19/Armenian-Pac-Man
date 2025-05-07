#ifndef DRAM_H
#define DRAM_H

#include "SFML/Graphics.hpp"
#include "GameElements.h"


class Dram {
    sf::Texture DramImage;
    sf::Sprite Dram_spr;

    public:
        Dram() {
            DramImage.loadFromFile("images/dram.png");
            Dram_spr.setTexture(DramImage);

            Dram_spr.setScale(15.f / 330.f, 10.f / 179.f);
        }

        void drawDram(sf::RenderWindow& window, int i, int j) {
            Dram_spr.setPosition(j * min_x, i * min_y);
            window.draw(Dram_spr);
        }

        sf::Sprite& getDramSprite() {
            return Dram_spr;
        }
};

#endif //DRAM_H