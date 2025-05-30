#include "Ghost.h"

class Clyde : public Ghost {
    public:
        Clyde(int i, int j) : Ghost(i, j, GhostType::Orange) {};
        Clyde() = delete;
        Clyde(const Clyde& other) : Ghost(other) {};
        Clyde(Clyde&& other) : Ghost(std::move(other)) {};
        Clyde& operator=(const Clyde& other);
        Clyde& operator=(Clyde&& other);

        std::pair<Directions, sf::Vector2f> ClydeHesitating(Map& map, Pacman& pac);
        virtual void move(Map& map, Pacman& pac, float deltaTime) override;
        int manhattanDist(int x1, int y1, int x2, int y2);
};
