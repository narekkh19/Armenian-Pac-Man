#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <array>
#include <vector>
#include <algorithm>
#include "SFML/Graphics.hpp"

bool isFood {}; 
std::vector<std::vector<int>> nums = {
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,5,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,2},
    {2,3,3,2,3,3,3,3,3,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2},
    {2,3,3,3,2,3,3,3,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2},
    {2,3,3,3,3,2,3,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2},
    {2,3,3,3,3,3,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2},
    {2,3,3,3,3,3,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2},
    {2,3,3,3,3,3,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2},
    {2,3,3,3,3,3,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2},
    {2,3,3,3,3,3,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2},
    {2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2},
    {2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,4,4,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2},
    {2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,4,4,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2},
    {2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2},
    {2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2},
    {2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,0,0,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2},
    {2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2},
    {2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2},
    {2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2},
    {2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2},
    {2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2},
    {2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
};


void eatCurrentfood(const sf::Vector2f& position) {
    int posx = position.x / 34;
    int posy = position.y / 30;
    if (nums[posy][posx] == 0) {
        nums[posy][posx] = -1;
    }
}

bool isValidBlock(int posx, int posy) {
    posx = posx / 34;
    posy = posy / 30;
    return nums[posy][posx] != 1;
}

void foo(sf::RenderWindow& w, sf::Sprite& sp, sf::Sprite& f, sf::Sprite& gh) {
    for (int i = 0; i < nums.size(); ++i) {
        for (int j = 0; j < nums[i].size(); ++j) {
            if (nums[i][j] == 2) {
                float entityWidth = 34.f;
                float entityHeight = 30.f;
                sf::FloatRect spriteBounds = sp.getGlobalBounds();
                float cellX = j * entityWidth;
                float cellY = i * entityHeight;
                float offsetX = (entityWidth - spriteBounds.width) / 2.f;
                float offsetY = (entityHeight - spriteBounds.height) / 2.f;
                
                sp.setPosition(cellX + offsetX, cellY + offsetY);
                w.draw(sp);
            } else if (nums[i][j] == 0) {
                f.setPosition(j * 34, i * 30);
                w.draw(f);
            }
            else if (nums[i][j] == 2) {
                gh.setPosition(j * 34, i * 30);
                w.draw(gh);
            }
        }
    }
}


void ghostMove(const sf::Sprite& gh) {
    std::vector<std::pair<int, int>> dirs {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
     
    std::random_device rd;
    std::mt19937 gen(rd());

    std::array<int, 4> indecies {0, 1, 2, 3}; 
    std::shuffle(indecies.begin(), indecies.end(), gen);

    for (int i : indecies) {

        int posx = gh.getPosition().x / 34 + dirs[i].first;
        int posy = gh.getPosition().y / 30 + dirs[i].second;
        
        if (posx >= 0 && posy >= 0 && posx < nums.size() && posy < nums.size()) {
            if (nums[posy][posx] != 1) {
                if (isFood) {
                    nums[gh.getPosition().y][gh.getPosition().x] = 0;
                } 
                
                if (nums[posy][posx] == 0) {
                    isFood = true;
                } else isFood = false;

                nums[posy][posx] = 2;
                return;
            }
        }
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode({1360, 690}), "Pac-Man");

    sf::Texture pacmanImage;
    pacmanImage.loadFromFile("./images/18.png");

    sf::Texture blockImage;
    blockImage.loadFromFile("./images/stone.png");
    
    sf::Texture foodImage;
    foodImage.loadFromFile("./images/food.png");

    sf::Texture tuft;
    tuft.loadFromFile("./images/dram.png");
    sf::Sprite tuf(tuft);

    tuf.setScale(15.f / 330.f, 10.f / 179.f);




    sf::Texture ghostImage;

    sf::Sprite ghosttmp(ghostImage);
    ghosttmp.setTextureRect(sf::IntRect(0,0, 50, 50));
    ghosttmp.setScale(34.f / 50.f, 30.f / 50.f);

    sf::Sprite food(foodImage);
    food.setTextureRect(sf::IntRect(143,128,18, 16));
    food.setScale(34.f / 18.f, 30.f / 16.f);

    sf::Sprite block(blockImage);
    block.setTextureRect(sf::IntRect(1, 1, 32, 32));
    block.setScale(34.f / 32.f, 30.f / 32.f);

    window.clear(sf::Color::Black);
    foo(window, block, food, ghosttmp);
    window.display();

    sf::Sprite Rhalfopen(pacmanImage);
    sf::Sprite Rfullopened(pacmanImage);
    sf::Sprite Rclosed(pacmanImage);
    
    sf::Sprite Lhalfopen(pacmanImage);
    sf::Sprite Lfullopened(pacmanImage);
    sf::Sprite Lclosed(pacmanImage);
    
    sf::Sprite Uphalfopen(pacmanImage);
    sf::Sprite Upfullopened(pacmanImage);
    sf::Sprite Upclosed(pacmanImage);

    sf::Sprite Dhalfopen(pacmanImage);
    sf::Sprite Dfullopened(pacmanImage);
    sf::Sprite Dclosed(pacmanImage);

    Rclosed.setTextureRect(sf::IntRect(3 * 15, 0 * 15, 15, 15));
    Rhalfopen.setTextureRect(sf::IntRect(4 * 15, 0 * 15, 15, 15));
    Rfullopened.setTextureRect(sf::IntRect(5 * 15, 0 * 15, 15, 15));

    Lclosed.setTextureRect(sf::IntRect(0 * 15, 0 * 15, 15, 15));
    Lhalfopen.setTextureRect(sf::IntRect(1 * 15, 0 * 15, 15, 15));
    Lfullopened.setTextureRect(sf::IntRect(2 * 15, 0 * 15, 15, 15));

    Upclosed.setTextureRect(sf::IntRect(6 * 15, 0 * 15, 15, 15));
    Uphalfopen.setTextureRect(sf::IntRect(7 * 15, 0 * 15, 15, 15));
    Upfullopened.setTextureRect(sf::IntRect(8 * 15, 0 * 15, 15, 15));

    Dclosed.setTextureRect(sf::IntRect(9 * 15, 0 * 15, 15, 15));
    Dhalfopen.setTextureRect(sf::IntRect(10 * 15, 0 * 15, 15, 15));
    Dfullopened.setTextureRect(sf::IntRect(11 * 15, 0 * 15, 15, 15));

    float scaleX = 34.f / 15.f;
    float scaleY = 2.f;

    Lclosed.setScale(scaleX, scaleY);
    Lhalfopen.setScale(scaleX, scaleY);
    Lfullopened.setScale(scaleX, scaleY);
    
    Rclosed.setScale(scaleX, scaleY);
    Rhalfopen.setScale(scaleX, scaleY);
    Rfullopened.setScale(scaleX, scaleY);

    Upclosed.setScale(scaleX, scaleY);
    Uphalfopen.setScale(scaleX, scaleY);
    Upfullopened.setScale(scaleX, scaleY);

    Dclosed.setScale(scaleX, scaleY);
    Dhalfopen.setScale(scaleX, scaleY);
    Dfullopened.setScale(scaleX, scaleY);

    std::vector<sf::Sprite*> Rframes = {&Rfullopened, &Rhalfopen, &Rclosed, &Rhalfopen};
    std::vector<sf::Sprite*> Lframes = {&Lfullopened, &Lhalfopen, &Lclosed, &Lhalfopen};
    std::vector<sf::Sprite*> Upframes = {&Upfullopened, &Uphalfopen, &Upclosed, &Uphalfopen};
    std::vector<sf::Sprite*> Dframes = {&Dfullopened, &Dhalfopen, &Dclosed, &Dhalfopen};
    
    int frameIndex = 0;
    sf::Clock animationClock;
    float frameTime = 0.15f; // seconds per frame
    std::vector<sf::Sprite*>* currDirection {&Rframes};
    
    
    sf::Vector2f position(34, 30);
    for (auto* s : *currDirection) s->setPosition(position);
    
    sf::Event::KeyEvent currKey {};
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
            window.close();
            
            if (event.type == sf::Event::KeyPressed) {
                currKey.code = event.key.code;
            }    
        }
        
        switch (currKey.code) {
            case sf::Keyboard::Left:
            if (position.x - 34 >= 0) {
                if (isValidBlock(position.x - 34, position.y)) {
                    position.x -= 34;
                    currDirection = &Lframes;
                    }
                } 
                break;

            case sf::Keyboard::Right:
                if (position.x + 34 < 1360) {
                    if (isValidBlock(position.x + 34, position.y)) {
                        position.x += 34;
                        currDirection = &Rframes;
                    }
                }
                break;

            case sf::Keyboard::Up:
                if (position.y - 30 >= 0) {
                    if (isValidBlock(position.x, position.y - 30)) {
                        position.y -= 30;
                        currDirection = &Upframes;
                    }
                }
                break;

            case sf::Keyboard::Down:
                if (position.y + 30 < 690) {
                    if (isValidBlock(position.x, position.y + 30)) {
                        position.y += 30;
                        currDirection = &Dframes;
                    }
                }
                break;
        }
        for (auto* s : *currDirection) s->setPosition(position);
                

        if (animationClock.getElapsedTime().asSeconds() > frameTime) {
            frameIndex = (frameIndex + 1) % currDirection->size();
            animationClock.restart();
        }

        window.clear(sf::Color::Black);
        eatCurrentfood(position);
        ghostMove(ghosttmp);
        foo(window, tuf, food, ghosttmp);
        window.draw(*(*currDirection)[frameIndex]);
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
