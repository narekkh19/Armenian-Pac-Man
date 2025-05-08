#ifndef TUFIBLOCK_H
#define TUFIBLOCK_H

#include "SFML/Graphics.hpp"
#include "GameElements.h"

class TufiBlock {
    sf::Texture TufiBlockImage;
    sf::Sprite tuf_spr;

    public:

    TufiBlock() {
        TufiBlockImage.loadFromFile("images/tuf.png");
        tuf_spr.setTexture(TufiBlockImage);

        tuf_spr.setScale(34.f / TufiBlockImage.getSize().x, 30.f / TufiBlockImage.getSize().y);
    }

    void drawTuF(sf::RenderWindow& window, int i, int j) {
        tuf_spr.setPosition(j * tile_x, i * tile_y);
        window.draw(tuf_spr);
    }

    sf::Sprite& getTufBlock() {
        return tuf_spr;
    }

};


#endif //TUFIBLOCK_H