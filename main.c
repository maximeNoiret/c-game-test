#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "term.h"

typedef struct Player {
  size_t x;
  size_t y;
} Player;

char *setPos(char *buf, unsigned x, unsigned y) {
  snprintf(buf, 15, "\033[%d;%dH", y, x);
  return buf;
}

int main() {

  char c;
  set_input_mode ();

  Player player = {1, 1};

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

  printf(CRS_HIDE FG_GREEN "%s@" RST LEFT, setPos(buf, player.x+1, player.y+1));
  fflush(stdout);

  char map[TERMINAL_HEIGHT][TERMINAL_WIDTH] = {"####################",
                                               "#   #######    #####",
                                               "#              #   #",
                                               "######### #####    #",
                                               "##                 #",
                                               "######### ###      #",
                                               "#   ##### ##########",
                                               "#                 ##",
                                               "#   ##########      ",
                                               "####################",};

  for(;;) {
    read(STDIN_FILENO, &c, 1);
    switch(c) {
        case 'z': case 'Z':
          if (player.y == 1 || map[player.y-1][player.x] == '#') break;
          --player.y;
          printf(" " LEFT UP FG_GREEN "@" RST LEFT);
          break;
        case 's': case 'S':
          if (player.y == TERMINAL_HEIGHT-2 || map[player.y+1][player.x] == '#') break;
          ++player.y;
          printf(" " LEFT DOWN FG_GREEN "@" RST LEFT);
          break;
        case 'q': case 'Q':
          if (player.x == 1 || map[player.y][player.x-1] == '#') break;
          --player.x;
          printf(" " LEFT LEFT FG_GREEN "@" RST LEFT);
          break;
        case 'd': case 'D':
          if (player.x == TERMINAL_WIDTH-2 || map[player.y][player.x+1] == '#') break;
          ++player.x;
          printf(" " FG_GREEN "@" RST LEFT);
          break;

        case '\004': goto fuckyouimusingalabel;
    }
    // discover surrounding tiles
    if (player.x != 1)                  printf(LEFT  "%c"          , map[player.y][player.x-1] ? map[player.y][player.x-1] : ' ');
    if (player.x != TERMINAL_WIDTH-2)   printf(RIGHT "%c" LEFT LEFT, map[player.y][player.x+1] ? map[player.y][player.x+1] : ' ');
    if (player.y != 1)                  printf(UP    "%c" LEFT DOWN, map[player.y-1][player.x] ? map[player.y-1][player.x] : ' ');
    if (player.y != TERMINAL_HEIGHT-2)  printf(DOWN  "%c" LEFT UP  , map[player.y+1][player.x] ? map[player.y+1][player.x] : ' '); 
    fflush(stdout);
  }
fuckyouimusingalabel:
  printf("%s" CRS_SHOW "Exiting...\n", setPos(buf, 0, TERMINAL_HEIGHT+1));
  return 0;
}