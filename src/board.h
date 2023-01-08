//Header file to represent board and board operations
#ifndef __BOARD_H__
#define __BOARD_H__

#include "chessStructs.h"

Board *createGameBoard(Color first); //allocate memory for gameboard

void deleteGameBoard(Board *gameBoard); //deallocate memory for gameboard

void populateGameBoard(Board *gameBoard, int rev); //sets the initial positions for all the game pieces

Color getGameTurn(Board *gameBoard); //return whose turn it is

void changeGameTurn(Board *gameBoard);

#endif
