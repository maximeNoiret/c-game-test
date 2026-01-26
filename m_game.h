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


char **gamemap_init(const unsigned h, const unsigned w);
void gamemap_free(GameState *gs, const unsigned h, const unsigned w);

bool process_input(GameState *gs, const char c);

#endif // M_GAME_H_