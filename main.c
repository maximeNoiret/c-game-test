#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "m_game.h"
#include "term.h"








int main() {
  set_input_mode();

  char buf[15];
  GameState gs;
  gs.map = gamemap_init(TERMINAL_HEIGHT, TERMINAL_WIDTH);
  gs.player.x = 1;
  gs.player.y = 1;

  draw_outline();

  printf("%sPos: %uX %uY", setPos(buf, 0, TERMINAL_HEIGHT+3), gs.player.x, gs.player.y);
  printf("%sGoal: ??X ??Y", setPos(buf, 20, TERMINAL_HEIGHT+3));
  printf(CRS_HIDE FG_GREEN BG_PATH ITALIC "%s@" RST LEFT, setPos(buf, gs.player.x, gs.player.y));

  memcpy(gs.map[0], "####################", 20);
  memcpy(gs.map[1], "#   #######    #####", 20);
  memcpy(gs.map[2], "#              #   #", 20);
  memcpy(gs.map[3], "######### #####    #", 20);
  memcpy(gs.map[4], "##                 #", 20);
  memcpy(gs.map[5], "######### ###      #", 20);
  memcpy(gs.map[6], "#   ##### ##########", 20);
  memcpy(gs.map[7], "#                 ##", 20);
  memcpy(gs.map[8], "#   ##########      ", 20);
  memcpy(gs.map[9], "####################", 20);

  /* MAIN LOOP */
  for(char c = '\0'; process_input(&gs, c); read(STDIN_FILENO, &c, 1)) {
    discover(&gs);
    fflush(stdout);
  }

  /* CLEANUP */
  gamemap_free(&gs, TERMINAL_HEIGHT, TERMINAL_WIDTH);
  printf(CLEAR CRS_SHOW "Exiting...\n");
  return 0;
}