#ifndef PACMAN_H
#define PACMAN_H
#include <vector>
#include "SFML/Graphics.hpp"
#include "GameElements.h"

class Map;

class Pacman {
    sf::Texture pacmanImage;
    std::vector<sf::Sprite> Upframes;
    std::vector<sf::Sprite> Rframes;
    std::vector<sf::Sprite> Dframes; 
    std::vector<sf::Sprite> Lframes; 
    sf::Vector2f currPos;
    Directions currDir;
    sf::Vector2f startPos;  // NEW: Needed for smooth linear movement
    sf::Vector2f targetPos;      // the tile‐center we’re sliding toward
    static constexpr int Pacman_Directions = 12;
    Directions requestedDir;
    float   moveProgress = 1.f;  // 0→1 progress of slide (1 means “arrived”)
    float   moveDuration = 0.2f; // seconds to slide one tile
    sf::Keyboard::Key nextKey;
    bool PacmanWin = false;
    bool PacmanDied = false;
    int score = 0;

    public:

        Pacman();
        Pacman(const Pacman& other);
        Pacman& operator= (const Pacman& other);
        std::vector<sf::Sprite>& getCurrDirection();
        sf::Vector2f getCurrPosition();
        Directions getcurrDir();
        void setCurrPosition(int i, int j);
        void PacmanMovement(sf::Event::KeyEvent currKey, Map& map, float deltaTime);
        bool isValidPosition(const sf::Vector2f& nextPos, const Map& map) const;
        void eat(const sf::Vector2f& nextPos, Map& map);
        void setWin(bool flag);
        void setDied(bool flag);
        bool winAnimation(sf::RenderWindow& window);
        bool lastWord(sf::RenderWindow& window);
        void draw(sf::RenderWindow& window,  int pac_frameindex);
        int getScore();
};

#endif //PACMAN_H
