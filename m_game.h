#ifndef M_GAME_H_
#define M_GAME_H_

/**
 * @brief Player struct to store information related to the player.
 */ 
typedef struct Player {
  unsigned x;  ///< x position of the player
  unsigned y;  ///< y position of the player
} Player;

typedef struct GameMap {
  unsigned w;
  unsigned h;
  char **ptr;
} GameMap;

typedef struct GameState {
  GameMap map;
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
void gamemap_free(GameState *gs);

/**
 * @brief Process the user input.
 * @param gs GameState
 * @param c User input in the form of a char
 * @return false is Ctrl+D, true otherwise
 */
bool process_input(GameState *gs, const char c);

#endif // M_GAME_H_