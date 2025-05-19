#ifndef FONT_H
#define FONT_H

#include "SFML/Graphics.hpp"
#include "GameElements.h"

class Font {
    sf::Font font;
    sf::Text text;

    public: 
        Font() {
            font.loadFromFile("/home/narek/Downloads/Noto_Sans_Armenian,Ubuntu/Noto_Sans_Armenian/NotoSansArmenian-VariableFont_wdth,wght.ttf");
            text.setFont(font);
            text.setCharacterSize(24);
            text.setFillColor(sf::Color::Black);
            text.setPosition(static_cast<float>(tile_y) * 20, -2);
        }

        void draw(sf::RenderWindow& window, int score) {
            text.setString(L"Score: " + std::to_wstring(score) + L" Դրամ");
            window.draw(text);
        }
};

#endif //FONT_H