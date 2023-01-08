#ifndef __MOVE_H__
#define __MOVE_H__

#include "networkStructs.h"

typedef struct moveStruct Move;

struct moveStruct
{
  int startX;
  int startY;
  int endX;
  int endY;
};

Move *createMove(Square *startSquare, Square *endSquare);

void deleteMove(Move *move);

void sendMove(Square *startSquare, Square *endSquare);  //user calls sendMove in order to send the move to server, no need to call createMove


#endif