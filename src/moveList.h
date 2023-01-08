//header file for move list functions
#ifndef __MOVELIST_H__
#define __MOVELIST_H__

#include "chessStructs.h"

MoveList *createMoveList(void); //allocate memory for linked list

MoveListNode *createMoveListNode(void); //allocate memory for list node

void appendMove(Square *start, Square *end, MoveList *list, double moveValue); //append a move to the list

void removeMoveNode(MoveListNode *node, MoveList *list); //remove a node from the list

void deleteMoveList(MoveList *moveList); //deallocate memory for linked list

void deleteMoveListNode(MoveListNode *moveListNode); //deallocate memory for list node

void appendMoveLists(MoveList *firstList, MoveList *secondList); //append two move lists

void analyzeMoveList(MoveList *list, Board *gameBoard); //go through the movelist and assign values to each move

#endif