#ifndef TERMIOSMANAGEMENT_H_
#define TERMIOSMANAGEMENT_H_

#define CLEAR "\x1B[2J\x1B[H"
#define RST   "\x1B[0m"

#define ITALIC     "\x1B[3m"
#define ITALIC_END "\x1B[23m"

#define FG_GREEN "\x1B[1;32m"
#define BG_GREEN "\x1B[1;42m"
#define BG_GRAY  "\x1B[48;5;236m"

#define BG_PATH  BG_GRAY

#define UP    "\x1B[1A"
#define DOWN  "\x1B[1B"
#define RIGHT "\x1B[1C"
#define LEFT  "\x1B[1D"

#define CRS_HIDE "\x1B[?25l"
#define CRS_SHOW "\x1B[?25h"
#define CRS_GETP "\033[6n"


#define MAP_HEIGHT gs->map.h
#define MAP_WIDTH  gs->map.w

#include "m_game.h"


/* TERMIOS */
/**
 * @brief Disables cannonical mode to allow direct input using Termios.
 * @note Function taken from official GNU documentation's example.
 */
void set_input_mode(void);


/* other */
/**
 * @brief Outputs into rows and cols the current size of the terminal.
 * @param[out] rows Current rows count of the terminal
 * @param[out] cols Current columns count of the terminal
 * @note This function is not used yet. It will be once the game is more built up.
 */
void get_terminal_size(unsigned *rows, unsigned *cols);

/**
 * @brief Generates the ANSI escape sequence to place the terminal cursor to a position.
 * @param[out] buf Buffer to store the generated ANSI escape sequence
 * @param[in]  x   Desired x position of the cursor
 * @param[in]  y   Desired y position of the cursor
 * @return The buffer to allow inline printing with printf()
 */
char *setPos(char *buf, unsigned x, unsigned y);

/**
 * @brief Draws the outline of the game map.
 * \note
 * The defined values (MAP_HEIGHT/WIDTH) have an incorrect name and should be MAP_HEIGHT/WIDTH.
 * This must be fixed soon.
 */
void draw_outline(GameState *gs);

/**
 * @brief Moves the player up.
 * @param[in,out] gs GameState to update internal player position
 */
void t_move_up   (GameState *gs);

/**
 * @brief Moves the player down.
 * @param[in,out] gs GameState to update internal player position
 */
void t_move_down (GameState *gs);

/**
 * @brief Moves the player left.
 * @param[in,out] gs GameState to update internal player position
 */
void t_move_left (GameState *gs);

/**
 * @brief Moves the player right.
 * @param[in,out] gs GameState to update internal player position
 */
void t_move_right(GameState *gs);

/**
 * @brief "Discovers" the four tiles around the player.
 * @param[in,out] gs GameState to access player position and map
 */
void discover(GameState *gs);



#endif // TERMIOSMANAGEMENT_H_