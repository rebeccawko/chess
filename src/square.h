//Header file to represent each square in the board
#ifndef __SQUARE_H__
#define __SQUARE_H__

#include "chessStructs.h"

Square *createSquare(int x, int y); //returns new instance of square struct
void deleteSquare(Square *square);  //deletes memory for the square struct

int getSquareXPos(const Square *square); //returns file (column) of square
int getSquareYPos(const Square *square); //returns rank (row) of square

ChessPiece *getChessPiece(const Square *square); //return the chess piece on this square

#endif