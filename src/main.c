#include <stdio.h>

#include "chessStructs.h"
#include "board.h"
#include "square.h"
#include "pieces.h"
#include "player.h"
#include "moveList.h"

int main()
{

  /* Game setup */
  Board *thisGameBoard = createGameBoard(BLACK); //This can be edited per test case
  populateGameBoard(thisGameBoard, 0);
  Player *player1 = createPlayer(WHITE, HUMAN);
  Player *player2 = createPlayer(BLACK, COMPUTER);
  thisGameBoard->player1 = player1;
  thisGameBoard->player2 = player2;
  fillPlayerPieces(player1, thisGameBoard);
  fillPlayerPieces(player2, thisGameBoard);

  int run = 1;

  while (run == 1)
  {

    if (thisGameBoard->playerTurn == BLACK)
    {
      AIHardMove(player2, thisGameBoard);
    }
  }

  //ChessPiece *pieceToMove = thisGameBoard->chessBoard[3][1]->thisSquaresPiece;
  //Square *endSquare = thisGameBoard->chessBoard[3][3];

  moveChessPiece(thisGameBoard->chessBoard[2][1]->thisSquaresPiece, thisGameBoard->chessBoard[2][3], thisGameBoard);
  moveChessPiece(thisGameBoard->chessBoard[1][6]->thisSquaresPiece, thisGameBoard->chessBoard[1][5], thisGameBoard);
  moveChessPiece(thisGameBoard->chessBoard[0][1]->thisSquaresPiece, thisGameBoard->chessBoard[0][3], thisGameBoard);
  moveChessPiece(thisGameBoard->chessBoard[2][7]->thisSquaresPiece, thisGameBoard->chessBoard[0][5], thisGameBoard);
  moveChessPiece(thisGameBoard->chessBoard[0][3]->thisSquaresPiece, thisGameBoard->chessBoard[0][4], thisGameBoard);
  moveChessPiece(thisGameBoard->chessBoard[1][5]->thisSquaresPiece, thisGameBoard->chessBoard[1][4], thisGameBoard);
  moveChessPiece(thisGameBoard->chessBoard[2][3]->thisSquaresPiece, thisGameBoard->chessBoard[2][4], thisGameBoard);
  moveChessPiece(thisGameBoard->chessBoard[2][6]->thisSquaresPiece, thisGameBoard->chessBoard[2][5], thisGameBoard);
  moveChessPiece(thisGameBoard->chessBoard[3][1]->thisSquaresPiece, thisGameBoard->chessBoard[3][2], thisGameBoard);
  moveChessPiece(thisGameBoard->chessBoard[3][7]->thisSquaresPiece, thisGameBoard->chessBoard[0][4], thisGameBoard);
  moveChessPiece(thisGameBoard->chessBoard[1][0]->thisSquaresPiece, thisGameBoard->chessBoard[2][2], thisGameBoard);
  moveChessPiece(thisGameBoard->chessBoard[0][4]->thisSquaresPiece, thisGameBoard->chessBoard[0][2], thisGameBoard);
  moveChessPiece(thisGameBoard->chessBoard[2][2]->thisSquaresPiece, thisGameBoard->chessBoard[4][3], thisGameBoard);
  moveChessPiece(thisGameBoard->chessBoard[0][2]->thisSquaresPiece, thisGameBoard->chessBoard[0][4], thisGameBoard);
  moveChessPiece(thisGameBoard->chessBoard[0][4]->thisSquaresPiece, thisGameBoard->chessBoard[0][2], thisGameBoard);
  moveChessPiece(thisGameBoard->chessBoard[0][2]->thisSquaresPiece, thisGameBoard->chessBoard[1][1], thisGameBoard);
  moveChessPiece(thisGameBoard->chessBoard[2][0]->thisSquaresPiece, thisGameBoard->chessBoard[1][1], thisGameBoard); //queen captured

  printf("here1");
  MoveListNode *n = AIHardMove(player2, thisGameBoard);
  printf("here");
}
