#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "m_game.h"
#include "m_file.h"
#include "term.h"


int main() {
  set_input_mode();

  char buf[15];
  GameState gs;
  gs.map.h = 24;
  gs.map.w = 80;
  gs.map.ptr = gamemap_init(gs.map.h, gs.map.w);
  gs.player.x = 1;
  gs.player.y = 1;

  draw_outline(&gs);

  printf("%sPos: %uX %uY", setPos(buf, 0, gs.map.h+3), gs.player.x, gs.player.y);
  printf("%sGoal: ??X ??Y", setPos(buf, 20, gs.map.h+3));
  printf(CRS_HIDE FG_GREEN BG_PATH ITALIC "%s@" RST LEFT, setPos(buf, gs.player.x, gs.player.y));

  load_room(&gs, "map_test.txt", 10, 5);

  /* MAIN LOOP */
  for(char c = '\0'; process_input(&gs, c); read(STDIN_FILENO, &c, 1)) {
    discover(&gs);
    fflush(stdout);
  }

  /* CLEANUP */
  gamemap_free(&gs);
  printf(CLEAR CRS_SHOW "Exiting...\n");
  return 0;
}