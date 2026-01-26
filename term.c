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

static void printHud(GameState *gs) {
  char buf[15];
  printf("%sPos: %uX %uY   ", setPos(buf, 0, TERMINAL_HEIGHT+3), gs->player.x, gs->player.y);
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

static void print_tile(GameState *gs, unsigned x, unsigned y) {
  char tile = gs->map[y][x];
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

  printf("%s", setPos(buf, gs->player.x, gs->player.y));
}

void discover(GameState *gs) {
  if (gs->player.x > 1)                  print_tile(gs, gs->player.x-1, gs->player.y);
  if (gs->player.x < TERMINAL_WIDTH-2)   print_tile(gs, gs->player.x+1, gs->player.y);
  if (gs->player.y > 1)                  print_tile(gs, gs->player.x, gs->player.y-1);
  if (gs->player.y < TERMINAL_HEIGHT-2)  print_tile(gs, gs->player.x, gs->player.y+1);
} // discover