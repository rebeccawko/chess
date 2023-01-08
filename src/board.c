//source file for board functions
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "board.h"
#include "square.h"
#include "pieces.h"

Board *createGameBoard(Color first)
{

  Board *gameBoard = malloc(sizeof(Board));

  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      gameBoard->chessBoard[i][j] = createSquare(i, j);
    }
  }
  gameBoard->playerTurn = first; //the game starts with the WHITE player's first move
  gameBoard->gameStatus = PLAY;
  return gameBoard;
}

void deleteGameBoard(Board *gameBoard)
{
  assert(gameBoard);
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      deleteSquare(gameBoard->chessBoard[i][j]);
    }
  }

  free(gameBoard);
}

void populateGameBoard(Board *gameBoard, int rev)
{

  for (int i = 0; i < 8; i++)
  { //sets the 2 full rows of pawns
    gameBoard->chessBoard[i][1]->thisSquaresPiece = createChessPiece(WHITE, PAWN, gameBoard->chessBoard[i][1]);
  }

  for (int i = 0; i < 8; i++)
  {
    gameBoard->chessBoard[i][6]->thisSquaresPiece = createChessPiece(BLACK, PAWN, gameBoard->chessBoard[i][6]);
  }

  for (int i = 0; i < 8; i++)
  { //sets the 2 rows of rook, knight, bishop, queen, and king
    switch (i)
    {
    case 0:
      gameBoard->chessBoard[i][0]->thisSquaresPiece = createChessPiece(WHITE, ROOK, gameBoard->chessBoard[i][0]);
      break;
    case 1:
      gameBoard->chessBoard[i][0]->thisSquaresPiece = createChessPiece(WHITE, KNIGHT, gameBoard->chessBoard[i][0]);
      break;
    case 2:
      gameBoard->chessBoard[i][0]->thisSquaresPiece = createChessPiece(WHITE, BISHOP, gameBoard->chessBoard[i][0]);
      break;
    case 3:
      if(rev == 0)
        gameBoard->chessBoard[i][0]->thisSquaresPiece = createChessPiece(WHITE, QUEEN, gameBoard->chessBoard[i][0]);
      else
        gameBoard->chessBoard[i][0]->thisSquaresPiece = createChessPiece(WHITE, KING, gameBoard->chessBoard[i][0]);
      break;
    case 4:
      if(rev == 0)
        gameBoard->chessBoard[i][0]->thisSquaresPiece = createChessPiece(WHITE, KING, gameBoard->chessBoard[i][0]);
      else
        gameBoard->chessBoard[i][0]->thisSquaresPiece = createChessPiece(WHITE, QUEEN, gameBoard->chessBoard[i][0]);
      break;
    case 5:
      gameBoard->chessBoard[i][0]->thisSquaresPiece = createChessPiece(WHITE, BISHOP, gameBoard->chessBoard[i][0]);
      break;
    case 6:
      gameBoard->chessBoard[i][0]->thisSquaresPiece = createChessPiece(WHITE, KNIGHT, gameBoard->chessBoard[i][0]);
      break;
    case 7:
      gameBoard->chessBoard[i][0]->thisSquaresPiece = createChessPiece(WHITE, ROOK, gameBoard->chessBoard[i][0]);
      break;
    }
  }

  for (int i = 0; i < 8; i++)
  {
    switch (i)
    {
    case 0:
      gameBoard->chessBoard[i][7]->thisSquaresPiece = createChessPiece(BLACK, ROOK, gameBoard->chessBoard[i][7]);
      break;
    case 1:
      gameBoard->chessBoard[i][7]->thisSquaresPiece = createChessPiece(BLACK, KNIGHT, gameBoard->chessBoard[i][7]);
      break;
    case 2:
      gameBoard->chessBoard[i][7]->thisSquaresPiece = createChessPiece(BLACK, BISHOP, gameBoard->chessBoard[i][7]);
      break;
      case 3:
        if(rev == 0)
          gameBoard->chessBoard[i][7]->thisSquaresPiece = createChessPiece(BLACK, QUEEN, gameBoard->chessBoard[i][7]);
        else
          gameBoard->chessBoard[i][7]->thisSquaresPiece = createChessPiece(BLACK, KING, gameBoard->chessBoard[i][7]);
        break;
      case 4:
        if(rev == 0)
          gameBoard->chessBoard[i][7]->thisSquaresPiece = createChessPiece(BLACK, KING, gameBoard->chessBoard[i][7]);
        else
          gameBoard->chessBoard[i][7]->thisSquaresPiece = createChessPiece(BLACK, QUEEN, gameBoard->chessBoard[i][7]);
        break;
    case 5:
      gameBoard->chessBoard[i][7]->thisSquaresPiece = createChessPiece(BLACK, BISHOP, gameBoard->chessBoard[i][7]);
      break;
    case 6:
      gameBoard->chessBoard[i][7]->thisSquaresPiece = createChessPiece(BLACK, KNIGHT, gameBoard->chessBoard[i][7]);
      break;
    case 7:
      gameBoard->chessBoard[i][7]->thisSquaresPiece = createChessPiece(BLACK, ROOK, gameBoard->chessBoard[i][7]);
      break;
    }
  }
}

Color getGameTurn(Board *gameBoard)
{
  return gameBoard->playerTurn;
}

void changeGameTurn(Board *gameBoard)
{
  if (getGameTurn(gameBoard) == WHITE)
  {
    gameBoard->playerTurn = BLACK;
  }
  else
  {
    gameBoard->playerTurn = WHITE;
  }
}
