#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "m_game.h"


static int fpeek(FILE * const f) {
  const int c = fgetc(f);
  return c == EOF ? EOF : ungetc(c, f);
}

int load_room(GameState *gs, char *fn, unsigned x, unsigned y) {

  // TODO: check if x y is outside of map.

  FILE *f = fopen(fn, "r");
  if (!f) return -1;

  unsigned w, h;
  if (fscanf(f, "%u;%u", &w, &h) != 2) return -2;
  ++w;
  ++h;
  fseek(f, 1, SEEK_CUR);  // skip '\n' of first line

  // TODO: check if room will leave map boundary.

  for (unsigned i = 0; fpeek(f) != EOF && i < h; ++i) {
    fread(&gs->map[y+i][x], 1, w, f);
    fseek(f, 1, SEEK_CUR);  // +1 to skip '\n'
  }

  fclose(f);

  return 0;
}
