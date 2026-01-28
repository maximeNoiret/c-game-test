#ifndef M_GAME_H_
#define M_GAME_H_


typedef struct Player {
  unsigned x;
  unsigned y;
} Player;

typedef struct GameState {
  char **map;
  Player player;
} GameState;

/**
 * @brief Allocates space in the heap for the game map matrix.
 * @param h Desired height of the map.
 * @param w Desired width of the map.
 * @return Pointer to the allocated matrix, NULL if allocation failed.
 */
char **gamemap_init(const unsigned h, const unsigned w);

/**
 * @brief Frees the allocated game map matrix.
 * @param gs GameState that contains the map
 * @param h Height of the map
 * @param w Width of the map
 */
void gamemap_free(GameState *gs, const unsigned h, const unsigned w);

/**
 * @brief Process the user input.
 * @param gs GameState
 * @param c User input in the form of a char
 * @return false is Ctrl+D, true otherwise
 */
bool process_input(GameState *gs, const char c);

#endif // M_GAME_H_