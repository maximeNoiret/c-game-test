#ifndef M_FILE_H_
#define M_FILE_H_

#include "m_game.h"

/**
 * @brief Loads a room from a file into the game map
 * @param gs Current GameState
 * @param fn File Name that contains the room
 * @param x x position of the top left corner of the room
 * @param y y position of the top left corner of the room
 * @return 0 on success, -1 on incorrect origin, -2 on out of boundary, -3 on file open error, 
 * 
 * @note Yet to be implemented!
 */
int load_room(GameState *gs, char *fn, unsigned x, unsigned y);




#endif // M_FILE_H_