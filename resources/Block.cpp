#include "Block.h"


Block::Block() {
    TufiBlockImage.loadFromFile("images/tuf.png");
    tuf_spr.setTexture(TufiBlockImage);
    tuf_spr.setScale(static_cast<float>(tile_x) / TufiBlockImage.getSize().x, static_cast<float>(tile_y) / TufiBlockImage.getSize().y);

    KesTufiBlockImage.loadFromFile("images/kestuf.png");
    kestuf_spr.setTexture(KesTufiBlockImage);
    kestuf_spr.setScale(static_cast<float>(tile_x) / KesTufiBlockImage.getSize().x, static_cast<float>(tile_y) / KesTufiBlockImage.getSize().y);

    RedRoofImage.loadFromFile("images/redroof.png");
    roof_spr.setTexture(RedRoofImage);
    roof_spr.setScale(static_cast<float>(tile_x) / RedRoofImage.getSize().x, static_cast<float>(tile_y) / RedRoofImage.getSize().y);        
}

void Block::draw(sf::RenderWindow& window, GameIntities which, int i, int j) {
    sf::Sprite* curr {};
    switch (which) {
        case GameIntities::Tuf:
            curr = &tuf_spr;
            break;
        case GameIntities::KesTuf:
            curr = &kestuf_spr;
            break;
        case GameIntities::RedRoof:
            curr = &roof_spr;
            break;

        default: return;
    }

    curr->setPosition(j * tile_x, i * tile_y);
    window.draw(*curr);
}

sf::Sprite& Block::getBlock(GameIntities which) {
    if (which == GameIntities::Tuf) return tuf_spr;
    if (which == GameIntities::KesTuf) return kestuf_spr;
    return roof_spr;
}