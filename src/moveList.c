#include <assert.h>
#include <stdio.h>
#include "stdlib.h"

#include "moveList.h"
#include "pieces.h"
#include "player.h"

MoveList *createMoveList(void)
{
  MoveList *moveList = malloc(sizeof(MoveList));

  moveList->head = NULL;
  moveList->tail = NULL;
  moveList->length = 0;

  return moveList;
}

MoveListNode *createMoveListNode(void)
{
  MoveListNode *node = malloc(sizeof(MoveListNode));

  node->startSquare = NULL;
  node->endSquare = NULL;
  node->list = NULL;
  node->nextNode = NULL;

  return node;
}

void deleteMoveList(MoveList *moveList)
{
  assert(moveList);

  MoveListNode *current = NULL, *next = NULL;

  if (moveList->length != 0)
  {
    current = moveList->head;
    while (current)
    {
      next = current->nextNode;
      deleteMoveListNode(current);
      current = next;
    }
  }
  moveList->length = 0;
  moveList->head = NULL;
  moveList->tail = NULL;

  free(moveList);
}

void deleteMoveListNode(MoveListNode *node)
{
  assert(node);

  node->startSquare = NULL;
  node->endSquare = NULL;
  node->list = NULL;
  node->nextNode = NULL;

  free(node);
}

void appendMove(Square *start, Square *end, MoveList *list, double moveValue)
{

  assert(start);
  assert(end);
  assert(list);
  MoveListNode *newNode = createMoveListNode();

  newNode->startSquare = start;
  newNode->endSquare = end;
  newNode->list = list;
  newNode->moveValue = moveValue;
  newNode->nextNode = NULL;

  if (!(list->head))
  {
    list->head = newNode;
  }
  else
  {
    list->tail->nextNode = newNode;
  }

  list->tail = newNode;
  list->length++;
}

void removeMoveNode(MoveListNode *node, MoveList *list)
{
  MoveListNode *current = list->head, *prev = NULL;

  if (list->head == node)
  {
    free(current);
    return;
  }

  while (current != NULL && current != node)
  {
    prev = current;
    current = current->nextNode;
  }

  // if the node was not present in the list
  if (!current)
  {
    return;
  }

  prev->nextNode = current->nextNode;

  free(current);
}

void appendMoveLists(MoveList *firstList, MoveList *secondList) //will add everything from the second list onto the end of the first list. Also deletes the second list
{
  MoveListNode *current = secondList->head, *next;

  if (firstList->length == 0)
  {
    firstList->head = secondList->head;
    firstList->tail = secondList->tail;
    while (current)
    {
      next = current->nextNode;
      current->list = firstList;
      current = next;
    }
  }
  else if (secondList->length != 0)
  {
    firstList->tail->nextNode = secondList->head;
    firstList->tail = secondList->tail;

    while (current) //iterate through the second linked list and set its list member equal to the first list
    {
      next = current->nextNode;
      current->list = firstList;
      current = next;
    }
  }
  firstList->length += secondList->length;
  free(secondList);
}

void analyzeMoveList(MoveList *list, Board *gameBoard)
{
  MoveListNode *current = list->head, *next;

  for (int i = 0; i < list->length; ++i)
  {
    next = current->nextNode;
    double moveValue = 0.0;
    ChessPiece *thisPiece = current->startSquare->thisSquaresPiece;
    Square *destinationSquare = current->endSquare;

    if (movePutsOpponentKingInCheck(thisPiece, destinationSquare, gameBoard) == 1)
    {
      moveValue += 300; // add 300 to the movevalue if the move will put the opponent in check
    }
    if (checkValidMove(thisPiece, destinationSquare, gameBoard) == 2) //if there's a capture
    {
      if (movePutsPieceInDanger(thisPiece, destinationSquare, gameBoard) == 1) //analyzes a trade
      {
        moveValue += (getPieceValue(destinationSquare->thisSquaresPiece) - getPieceValue(thisPiece));
      }
      else //if the opponent has a hanging piece
      {
        moveValue += getPieceValue(destinationSquare->thisSquaresPiece);
      }
    }
    else if (movePutsPieceInDanger(thisPiece, destinationSquare, gameBoard) == 1) //if the piece is moved into a dangerous position
    {
      moveValue -= getPieceValue(thisPiece);
    }

    current->moveValue = moveValue;
    current = next;
  }
}