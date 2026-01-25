#ifndef TERMIOSMANAGEMENT_H_
#define TERMIOSMANAGEMENT_H_

#define CLEAR     "\x1B[2J\x1B[H"
#define RST       "\x1B[0m"
#define FG_GREEN  "\x1B[1;32m"
#define BG_GREEN  "\x1B[1;42m"

#define UP    "\x1B[1A"
#define DOWN  "\x1B[1B"
#define RIGHT "\x1B[1C"
#define LEFT  "\x1B[1D"

#define CRS_HIDE "\x1B[?25l"
#define CRS_SHOW "\x1B[?25h"
#define CRS_GETP "\033[6n"


#define TERMINAL_HEIGHT 24
#define TERMINAL_WIDTH  80

#include "m_game.h"


/* TERMIOS */
void set_input_mode (void);
void get_terminal_size(unsigned *rows, unsigned *cols);


/* other */
char *setPos(char *buf, unsigned x, unsigned y);

void t_move_up   (GameState *gs);
void t_move_down (GameState *gs);
void t_move_left (GameState *gs);
void t_move_right(GameState *gs);

void discover(GameState *gs);



#endif // TERMIOSMANAGEMENT_H_