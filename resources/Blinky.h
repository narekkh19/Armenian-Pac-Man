#include "Ghost.h"

class Blinky : public Ghost {
    public:
        Blinky(int i, int j) : Ghost(i, j, Ghosts::Red) {};
        Blinky() = delete;
        Blinky(const Blinky& other) : Ghost(other) {};
        Blinky(Blinky&& other) : Ghost(std::move(other)) {};
        Blinky& operator=(const Blinky& other);
        Blinky& operator=(Blinky&& other);

        std::pair<Directions, sf::Vector2f> shortestDirectiontoPacman(Map& map, const sf::Vector2f& pacmanPoss);
        virtual void move(Map& map, Pacman& pac, float deltaTime) override;
        int manhattanDist(int x1, int y1, int x2, int y2);
};
