#ifndef GAME_ELEMENTS
#define GAME_ELEMENTS

enum class MapDetails {None, Pacman, Block, Food, Ghosts, MegaFood};

enum class Ghosts {Red, Pink, Blue, Orange, Green, Violet}; 

enum class Directions { Left, Down, Right, Up };

static constexpr int window_x = 40;
static constexpr int window_y = 23;
static constexpr int min_x = 34;
static constexpr int min_y = 30;

#endif //GAME_ELEMENTS