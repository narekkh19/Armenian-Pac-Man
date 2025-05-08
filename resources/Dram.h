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
            sf::FloatRect spriteBounds = Dram_spr.getGlobalBounds();
            float cellX = j * tile_x;
            float cellY = i * tile_y;
            float offsetX = (tile_x - spriteBounds.width) / 2.f;
            float offsetY = (tile_y - spriteBounds.height) / 2.f;

            Dram_spr.setPosition(cellX + offsetX, offsetY + cellY);
            window.draw(Dram_spr);
        }

        sf::Sprite& getDramSprite() {
            return Dram_spr;
        }
};

#endif //DRAM_H