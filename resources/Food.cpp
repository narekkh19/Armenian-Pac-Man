#include "Food.h"


Food::Food() {
    DramImage.loadFromFile("images/dram.png");
    dram_spr.setTexture(DramImage);
    dram_spr.setScale(15.f / 330.f, 10.f / 179.f);

    XorovImage.loadFromFile("images/xorovac-removebg.png");
    xorov_spr.setTexture(XorovImage);
    xorov_spr.setScale(static_cast<float>(tile_x) / XorovImage.getSize().x, static_cast<float>(tile_y) / XorovImage.getSize().y);
}


void Food::draw(sf::RenderWindow& window, GameIntities type, int i, int j) {
    sf::Sprite* curr {};
    switch (type) {
        case GameIntities::Food:
            curr = &dram_spr;
            break;
        
        case GameIntities::MegaFood:
            curr = &xorov_spr;
            break;

        default: return;
    }

    if (type == GameIntities::Food) {

        sf::FloatRect spriteBounds = dram_spr.getGlobalBounds();
        float cellX = j * tile_x;
        float cellY = i * tile_y;
        float offsetX = (tile_x - spriteBounds.width) / 2.f;
        float offsetY = (tile_y - spriteBounds.height) / 2.f;
        dram_spr.setPosition(cellX + offsetX, offsetY + cellY);
    } else {
        xorov_spr.setPosition(j * tile_x, i * tile_y);
    }

    window.draw(*curr);
}