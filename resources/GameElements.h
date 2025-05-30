#ifndef GAME_ELEMENTS
#define GAME_ELEMENTS

enum class GameIntities {None, Pacman, Tuf, Food, Avenue, Ghosts, MegaFood, NonVisibleBlock};

enum class GhostType {Red, Pink, Blue, Orange}; 

enum class Directions { Up, Right, Down, Left, None};

static constexpr int winningScore = 216;
static constexpr int window_x = 40;
static constexpr int window_y = 23;
static constexpr int tile_x = 34;
static constexpr int tile_y = 30;

#endif //GAME_ELEMENTS