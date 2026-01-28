#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "m_game.h"


static int fpeek(FILE * const f) {
  const int c = fgetc(f);
  return c == EOF ? EOF : ungetc(c, f);
}

static void next_line(FILE *f) {
  char dummy[4];
  fgets(dummy, sizeof(dummy), f);
}

int load_room(GameState *gs, char *fn, unsigned x, unsigned y) {

  if (x < 0 || x > gs->map.w ||
      y < 0 || y > gs->map.h) return -1;

  FILE *f = fopen(fn, "r");
  if (!f) return -1;

  unsigned w, h;
  if (fscanf(f, "%u;%u", &w, &h) != 2) return -3;

  if (x+w > gs->map.w || y+h > gs->map.h) return -2;

  next_line(f);

  for (unsigned i = 0; fpeek(f) != EOF && i < h; ++i) {
    fread(&gs->map.ptr[y+i][x], 1, w, f);
    next_line(f);
  }

  fclose(f);

  return 0;
}
