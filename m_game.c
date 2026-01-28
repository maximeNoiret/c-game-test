#include <stdlib.h>

#include "m_game.h"
#include "term.h"

char **gamemap_init(const unsigned h, const unsigned w) {
  char **map = calloc(h, sizeof(char *));
  if (!map) return NULL;

  for (unsigned i = 0; i < h; ++i) {
    map[i] = calloc(w, sizeof(char));
    if (!map[i]) return NULL;
  }
  return map;
}

void gamemap_free(GameState *gs) {
  for (unsigned i = 0; i < gs->map.h; ++i) {
    free(gs->map.ptr[i]);
  }
  free(gs->map.ptr);
}

bool process_input(GameState *gs, const char c) {
  if (c == '\0') return true;
  switch(c) {
    case 'z': case 'Z':
      if (gs->player.y == 1 || gs->map.ptr[gs->player.y-1][gs->player.x] == '#') break;
      t_move_up(gs);
      break;
    case 's': case 'S':
      if (gs->player.y == gs->map.h-2 || gs->map.ptr[gs->player.y+1][gs->player.x] == '#') break;
      t_move_down(gs);
      break;
    case 'q': case 'Q':
      if (gs->player.x == 1 || gs->map.ptr[gs->player.y][gs->player.x-1] == '#') break;
      t_move_left(gs);
      break;
    case 'd': case 'D':
      if (gs->player.x == gs->map.w-2 || gs->map.ptr[gs->player.y][gs->player.x+1] == '#') break;
      t_move_right(gs);
      break;

    case '\004': return false;
  }
  return true;
}