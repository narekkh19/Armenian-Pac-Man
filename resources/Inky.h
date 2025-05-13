#include "Ghost.h"

class Inky : public Ghost {
    public:
        Inky(int i, int j) : Ghost(i, j) {};
        Inky() = delete;
        Inky(const Inky& other) : Ghost(other) {};
        Inky(Inky&& other) : Ghost(std::move(other)) {};
        
        Inky& operator=(const Inky& other);
        Inky& operator=(Inky&& other);

        std::pair<Directions, sf::Vector2f> InkysUnpredictableLogic(Map& map, Pacman& pac);
        virtual void move(Map& map, Pacman& pac, float deltaTime) override;
        int manhattanDist(int x1, int y1, int x2, int y2);
        std::pair<int, int> manhattanDistCoord(int x1, int y1, int x2, int y2);
};
