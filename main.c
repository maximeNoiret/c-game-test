#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "m_game.h"
#include "term.h"








int main() {

  char c;
  set_input_mode ();

  GameState gs;
  gs.map = gamemap_init(TERMINAL_HEIGHT, TERMINAL_WIDTH);
  gs.player.x = 1;
  gs.player.y = 1;

  char buf[15];
  // draw borders
  printf(CLEAR RST);
  for (unsigned i = 0; i < TERMINAL_WIDTH; ++i) printf("#");
  for (unsigned j = 1; j < TERMINAL_HEIGHT; ++j) {
    printf("%s#", setPos(buf, 0, j));
    printf("%s#", setPos(buf, TERMINAL_WIDTH, j));
  }
  printf("\n");
  for (unsigned i = 0; i < TERMINAL_WIDTH; ++i) printf("#");

  printf("%sPos: %uX %uY", setPos(buf, 0, TERMINAL_HEIGHT+3), gs.player.x, gs.player.y);
  printf("%sGoal: ?X ?Y", setPos(buf, 20, TERMINAL_HEIGHT+3));
  printf(CRS_HIDE FG_GREEN "%s@" RST LEFT, setPos(buf, gs.player.x+1, gs.player.y+1));
  fflush(stdout);

  memcpy(gs.map[0], "####################", 20);
  memcpy(gs.map[1], "#   #######    #####", 20);
  memcpy(gs.map[2], "#    ----      #   #", 20);
  memcpy(gs.map[3], "######### #####    #", 20);
  memcpy(gs.map[4], "##                 #", 20);
  memcpy(gs.map[5], "######### ###      #", 20);
  memcpy(gs.map[6], "#   ##### ##########", 20);
  memcpy(gs.map[7], "#                 ##", 20);
  memcpy(gs.map[8], "#   ##########      ", 20);
  memcpy(gs.map[9], "####################", 20);

  for(;;) {
    read(STDIN_FILENO, &c, 1);
    switch(c) {
        case 'z': case 'Z':
          if (gs.player.y == 1 || gs.map[gs.player.y-1][gs.player.x] == '#') break;
          t_move_up(&gs);
          break;
        case 's': case 'S':
          if (gs.player.y == TERMINAL_HEIGHT-2 || gs.map[gs.player.y+1][gs.player.x] == '#') break;
          t_move_down(&gs);
          break;
        case 'q': case 'Q':
          if (gs.player.x == 1 || gs.map[gs.player.y][gs.player.x-1] == '#') break;
          t_move_left(&gs);
          break;
        case 'd': case 'D':
          if (gs.player.x == TERMINAL_WIDTH-2 || gs.map[gs.player.y][gs.player.x+1] == '#') break;
          t_move_right(&gs);
          break;

        case '\004': goto exit;
    }
    // discover surrounding tiles
    if (gs.player.x > 1)                  printf(LEFT  "%c"          , gs.map[gs.player.y][gs.player.x-1] ? gs.map[gs.player.y][gs.player.x-1] : ' ');
    if (gs.player.x < TERMINAL_WIDTH-2)   printf(RIGHT "%c" LEFT LEFT, gs.map[gs.player.y][gs.player.x+1] ? gs.map[gs.player.y][gs.player.x+1] : ' ');
    if (gs.player.y > 1)                  printf(UP    "%c" LEFT DOWN, gs.map[gs.player.y-1][gs.player.x] ? gs.map[gs.player.y-1][gs.player.x] : ' ');
    if (gs.player.y < TERMINAL_HEIGHT-2)  printf(DOWN  "%c" LEFT UP  , gs.map[gs.player.y+1][gs.player.x] ? gs.map[gs.player.y+1][gs.player.x] : ' ');
    fflush(stdout);
  }
exit:
  gamemap_free(&gs, TERMINAL_HEIGHT, TERMINAL_WIDTH);
  printf(CLEAR CRS_SHOW "Exiting...\n");
  return 0;
}