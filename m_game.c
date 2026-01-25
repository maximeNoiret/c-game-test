#include <stdlib.h>

#include "m_game.h"

char **gamemap_init(const unsigned h, const unsigned w) {
  char **map = calloc(h, sizeof(char *));
  if (!map) return NULL;

  for (unsigned i = 0; i < h; ++i) {
    map[i] = calloc(w, sizeof(char));
    if (!map[i]) return NULL;
  }
  return map;
}

void gamemap_free(GameState *gs, const unsigned h, const unsigned w) {
  for (unsigned i = 0; i < h; ++i) {
    free(gs->map[i]);
  }
  free(gs->map);
}