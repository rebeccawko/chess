#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "square.h"
#include "pieces.h"

Square *createSquare(int x, int y)
{
  Square *newSquare = malloc(sizeof(Square));

  newSquare->xPos = x;
  newSquare->yPos = y;
  newSquare->thisSquaresPiece = NULL;

  return newSquare;
}

void deleteSquare(Square *square)
{
  assert(square);

  if (square->thisSquaresPiece)
  {
    deleteChessPiece(square->thisSquaresPiece);
  }

  free(square);
}

int getSquareXPos(const Square *square)
{
  assert(square);
  return square->xPos;
}

int getSquareYPos(const Square *square)
{
  assert(square);
  return square->yPos;
}

ChessPiece *getChessPiece(const Square *square)
{
  assert(square);
  if (square->thisSquaresPiece)
  {
    return square->thisSquaresPiece;
  }
  return NULL;
}