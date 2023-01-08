#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#define MAX_MSGLEN 100
#define SQUARE_SIZE 50
#define WINDOW_BORDER 10
#define BOARD_BORDER 10
#define BOARD_WIDTH (8 * SQUARE_SIZE)
#define BOARD_HEIGHT (8 * SQUARE_SIZE)
#define WINDOW_WIDTH (BOARD_WIDTH + 2 * BOARD_BORDER)
#define WINDOW_HEIGHT (BOARD_HEIGHT + 2 * BOARD_BORDER)
#define SLEN 64

typedef struct Game
{
  char Name[SLEN];
  int opponent;   // 0 for human, 1 for cpu
  int set_color;  // 0 for white, 1 for black
  int difficulty; //empty variable until difficulty functionality implented in future version
} newGame;

newGame current; //struct to access game settings
FILE *state;     //file saves state of game settings

#endif
