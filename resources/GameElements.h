#ifndef GAME_ELEMENTS
#define GAME_ELEMENTS

enum class MapDetails {None, Pacman, Block, Food, Ghosts, MegaFood};

enum class Ghosts {Red, Pink, Blue, Orange}; 

enum class Directions { Up, Right, Down, Left, None};

static constexpr int window_x = 40;
static constexpr int window_y = 23;
static constexpr int tile_x = 34;
static constexpr int tile_y = 30;

#endif //GAME_ELEMENTS