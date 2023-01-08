#include "move.h"
#include <stdlib.h>

Move *createMove(Square *startSquare, Square *endSquare)
{
  Move *newMove = malloc(sizeof(Move));

  newMove->startX = startSquare->xPos;
  newMove->startY = startSquare->yPos;
  newMove->endX = endSquare->xPos;
  newMove->endY = endSquare->yPos;

  return newMove;
}

void deleteMove(Move *move)
{
  free(move);
}

void sendMove(Square *startSquare, Square *endSquare) 
{
  Move *move = createMove(startSquare, endSquare);
}