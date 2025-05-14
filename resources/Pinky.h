#include "Ghost.h"

class Pinky : public Ghost {
    public:
        Pinky(int i, int j) : Ghost(i, j, Ghosts::Pink) {};
        Pinky() = delete;
        Pinky(const Pinky& other) : Ghost(other) {};
        Pinky(Pinky&& other) : Ghost(std::move(other)) {};
        Pinky& operator=(const Pinky& other);
        Pinky& operator=(Pinky&& other);

        int manhattanDist(int x1, int y1, int x2, int y2);
        std::pair<Directions, sf::Vector2f> DirectionAheadPacman(Map& map, Pacman& pac);
        virtual void move(Map& map, Pacman& pac, float deltaTime) override;
        std::pair<int, int> DirectionToCoord(Directions dir);
};
