    #include "Block.h"


    Block::Block() {
        TufiBlockImage.loadFromFile("images/tuf.png");
        tuf_spr.setTexture(TufiBlockImage);
        tuf_spr.setScale(static_cast<float>(tile_x) / TufiBlockImage.getSize().x, static_cast<float>(tile_y) / TufiBlockImage.getSize().y);

        HraparakImage.loadFromFile("images/hraparakai.png");
        hr_spr.setTexture(HraparakImage);
        hr_spr.setScale(38 * static_cast<float>(tile_x) / HraparakImage.getSize().x, 21 * static_cast<float>(tile_y) / HraparakImage.getSize().y);
    }

    void Block::draw(sf::RenderWindow& window, GameIntities which, int i, int j) {
        sf::Sprite* curr {};
        switch (which) {
            case GameIntities::Tuf:
                curr = &tuf_spr;
                break;
            case GameIntities::Avenue:
                curr = &hr_spr;
                break;

            default: return;
        }

        curr->setPosition(j * tile_x, i * tile_y);
        window.draw(*curr);
    }

    // sf::Sprite& Block::getBlock(GameIntities which) {
    //     if (which == GameIntities::Tuf) return tuf_spr;
    //     if (which == GameIntities::KesTuf) return kestuf_spr;
    //     return roof_spr;
    // }