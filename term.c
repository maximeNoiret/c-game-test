#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/ioctl.h>

#include "term.h"
#include "m_game.h"

struct termios saved_attributes;

static void reset_input_mode (void) {
  tcsetattr (STDIN_FILENO, TCSANOW, &saved_attributes);
} // reset_input_mode

void set_input_mode (void) {
  struct termios tattr;
/*  char *name;*/

  /* Make sure stdin is a terminal. */
  if (!isatty (STDIN_FILENO))
    {
      fprintf (stderr, "Not a terminal.\n");
      exit (EXIT_FAILURE);
    }

  /* Save the terminal attributes so we can restore them later. */
  tcgetattr (STDIN_FILENO, &saved_attributes);
  atexit (reset_input_mode);

  /* Set the funny terminal modes. */
  tcgetattr (STDIN_FILENO, &tattr);
  tattr.c_lflag &= ~(ICANON|ECHO); /* Clear ICANON and ECHO. */
  tattr.c_cc[VMIN] = 1;
  tattr.c_cc[VTIME] = 0;
  tcsetattr (STDIN_FILENO, TCSAFLUSH, &tattr);
} // set_input_mode



void get_terminal_size(unsigned *rows, unsigned *cols) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    *rows = w.ws_row;
    *cols = w.ws_col;
} // get_terminal_size


char *setPos(char *buf, unsigned x, unsigned y) {
  snprintf(buf, 15, "\033[%d;%dH", y+1, x+1);
  return buf;
} // setPos

void draw_outline(GameState *gs) {
  char buf[15];
  printf(CLEAR RST);
  printf("/");
  for (unsigned i = 1; i < gs->map.w-1; ++i) printf("-");
  printf("\\");
  for (unsigned j = 1; j < gs->map.h-1; ++j) {
    printf("%s|", setPos(buf, 0, j));
    printf("%s|", setPos(buf, gs->map.w-1, j));
  }
  printf("\n\\");
  for (unsigned i = 1; i < gs->map.w-1; ++i) printf("-");
  printf("/");
}


static void printHud(GameState *gs) {
  char buf[15];
  printf("%sPos: %uX %uY   ", setPos(buf, 0, gs->map.h+3), gs->player.x, gs->player.y);
  printf("%s", setPos(buf, gs->player.x+1, gs->player.y+1));
} // printHud

void t_move_up(GameState *gs) {
  --gs->player.y;
  printf(" " LEFT UP FG_GREEN BG_PATH ITALIC "@" RST LEFT);
  printHud(gs);
} // t_move_up

void t_move_down (GameState *gs) {
  ++gs->player.y;
  printf(" " LEFT DOWN FG_GREEN BG_PATH ITALIC "@" RST LEFT);
  printHud(gs);
} // t_move_down

void t_move_left (GameState *gs) {
  --gs->player.x;
  printf(" " LEFT LEFT FG_GREEN BG_PATH ITALIC "@" RST LEFT);
  printHud(gs);
} // t_move_left

void t_move_right(GameState *gs) {
  ++gs->player.x;
  printf(" " FG_GREEN BG_PATH ITALIC "@" RST LEFT);
  printHud(gs);
} // t_move_right

// WARNING: this function does not place back the cursor to player.
static void print_tile(GameState *gs, unsigned x, unsigned y) {
  char tile = gs->map.ptr[y][x];
  char buf[15];
  printf("%s", setPos(buf, x, y));

  switch (tile) {
    case ' ': case '\0':
      printf(BG_PATH " " RST);
      break;
    default:
      printf("%c", tile);
      break;
  }
}

void discover(GameState *gs) {
  char buf[15];
  if (gs->player.x > 1)            print_tile(gs, gs->player.x-1, gs->player.y);
  if (gs->player.x < gs->map.w-2)  print_tile(gs, gs->player.x+1, gs->player.y);
  if (gs->player.y > 1)            print_tile(gs, gs->player.x, gs->player.y-1);
  if (gs->player.y < gs->map.h-2)  print_tile(gs, gs->player.x, gs->player.y+1);
  printf("%s", setPos(buf, gs->player.x, gs->player.y));
} // discover