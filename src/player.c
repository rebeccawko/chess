//source file for player functions

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "player.h"
#include "pieces.h"
#include "moveList.h"
#include "square.h"

Player *createPlayer(Color color, PlayerType type)
{
  Player *newPlayer = malloc(sizeof(Player));

  newPlayer->playerColor = color;
  newPlayer->type = type;
  newPlayer->isInCheckmate = 0; //default a Player to not be in checkmate when it is created

  return newPlayer;
}

void deletePlayer(Player *player)
{
  free(player);
}

void deletePlayerPiece(ChessPiece *piece, Player *player)
{

  piece->square = NULL;

  for (int i = 0; i < (sizeof(player->playerPieces)) / sizeof(player->playerPieces[0]); i++)
  {
    if (piece == player->playerPieces[i])
      player->playerPieces[i] = NULL;
  }

  deleteChessPiece(piece);
}

void fillPlayerPieces(Player *player, Board *gameBoard)
{
  if (player->playerColor == WHITE)
  {
    for (int i = 0; i < 8; ++i)
    {
      player->playerPieces[i] = getChessPiece(gameBoard->chessBoard[i][0]);
      player->playerPieces[8 + i] = getChessPiece(gameBoard->chessBoard[i][1]);
    }
    player->playerKing = getChessPiece(gameBoard->chessBoard[4][0]);
  }

  else if (player->playerColor == BLACK)
  {
    for (int i = 0; i < 8; ++i)
    {
      player->playerPieces[i] = getChessPiece(gameBoard->chessBoard[i][7]);
      player->playerPieces[8 + i] = getChessPiece(gameBoard->chessBoard[i][6]);
    }
    player->playerKing = getChessPiece(gameBoard->chessBoard[4][7]);
  }
}

MoveList *getAllPossibleMoves(Player *player, Board *gameBoard)
{
  MoveList *possibleMoveList = createMoveList();
  for (int i = 0; i < sizeof(player->playerPieces) / sizeof(player->playerPieces[0]); ++i)
  {
    if (player->playerPieces[i] == NULL)
    {
      continue;
    }
    else
    {
      appendMoveLists(possibleMoveList, getValidMoves(player->playerPieces[i], gameBoard));
    }
  }
  return possibleMoveList;
}

ChessPiece *getOpponentPlayerKing(ChessPiece *piece, Board *gameBoard)
{
  ChessPiece *playerKing;

  if (piece->color == gameBoard->player1->playerColor)
  {
    playerKing = gameBoard->player2->playerKing;
  }
  else if (piece->color == gameBoard->player2->playerColor)
  {
    playerKing = gameBoard->player1->playerKing;
  }

  return playerKing;
}

ChessPiece *getPlayerKing(ChessPiece *piece, Board *gameBoard)
{
  ChessPiece *playerKing;

  if (piece->color == gameBoard->player1->playerColor)
  {
    playerKing = gameBoard->player1->playerKing;
  }
  else if (piece->color == gameBoard->player2->playerColor)
  {
    playerKing = gameBoard->player2->playerKing;
  }

  return playerKing;
}

/*
piece is the piece to move
 endSquare is the endSquare of the current move to verify if it will put the opponent's king in check on the next turn
 gameBoard is the current state of the game board
 */
int movePutsOpponentKingInCheck(ChessPiece *piece, Square *endSquare, Board *gameBoard)
{
  ChessPiece *originalEndSquarePiece; //keep track of the piece that was on the end square before trying the move
  Square *startSquare = piece->square;

  if (endSquare->thisSquaresPiece != NULL)
  {
    originalEndSquarePiece = endSquare->thisSquaresPiece;
  }
  else
  {
    originalEndSquarePiece = NULL;
  }

  ChessPiece *opponentKing = getOpponentPlayerKing(piece, gameBoard);

  piece->square->thisSquaresPiece = NULL; //temporarily move the piece to the end square
  endSquare->thisSquaresPiece = piece;
  piece->square = endSquare;

  if (checkValidMove(piece, getPiecesSquare(opponentKing), gameBoard) != 0)
  {
    piece->square = startSquare; //move the piece back to the right place
    startSquare->thisSquaresPiece = piece;
    endSquare->thisSquaresPiece = originalEndSquarePiece;
    return 1;
  }

  piece->square = startSquare; //move the piece back to the right place
  startSquare->thisSquaresPiece = piece;
  endSquare->thisSquaresPiece = originalEndSquarePiece;
  return 0;
}

/* piece is the piece the computer tries to move, endSquare is the square it wants to move to, gameBoard is the chess board */
int movePutsPieceInDanger(ChessPiece *piece, Square *endSquare, Board *gameBoard)
{
  Player *player, *opponent; //pointer to the player making the move and the opponent

  if (piece->color == gameBoard->player1->playerColor) //check for piece and player colors
  {
    player = gameBoard->player1;
    opponent = gameBoard->player2;
  }
  else if (piece->color == gameBoard->player2->playerColor)
  {
    player = gameBoard->player2;
    opponent = gameBoard->player1;
  }

  ChessPiece *originalEndSquarePiece = endSquare->thisSquaresPiece;
  Square *startSquare = piece->square;

  int capFlag = checkValidMove(piece, endSquare, gameBoard);
  if (capFlag == 2)
  {
    //temporarily move the piece to the endsquare
    piece->square->thisSquaresPiece = NULL;
    endSquare->thisSquaresPiece = piece;
    piece->square = endSquare;
  }

  MoveList *opponentMoves = getAllPossibleMoves(opponent, gameBoard);
  MoveList *playerMoves = getAllPossibleMoves(player, gameBoard);

  int opponentMovePossibility = 0; //keeps track if opponent can move to end square
  int endSquareProtect = 0;        //keeps track if the endsquare is protected by another move

  MoveListNode *currentOpponentMove = opponentMoves->head, *currentPlayerMove = playerMoves->head, *nextOpponentMove, *nextPlayerMove; //what move node in the linked list the iteration is on/next

  while (currentPlayerMove)
  {
    nextPlayerMove = currentPlayerMove->nextNode;

    if ((currentPlayerMove->startSquare->thisSquaresPiece) != piece && (currentPlayerMove->endSquare == endSquare))
    {
      endSquareProtect = 1;
      break;
    }
    currentPlayerMove = nextPlayerMove;
  }

  while (currentOpponentMove)
  {
    nextOpponentMove = currentOpponentMove->nextNode;

    if (currentOpponentMove->endSquare == endSquare)
    {
      opponentMovePossibility = 1;
      break;
    }

    currentOpponentMove = nextOpponentMove;
  }

  int endSquareProtected = (endSquareProtect == 1) ? 1 : 0;
  int opponentCanMove = (opponentMovePossibility == 1) ? 1 : 0;

  deleteMoveList(opponentMoves);
  deleteMoveList(playerMoves);

  if (capFlag == 2) //move the pieces back to the original spot if there was a capture
  {
    piece->square = startSquare;
    startSquare->thisSquaresPiece = piece;
    endSquare->thisSquaresPiece = originalEndSquarePiece;
  }

  if (opponentCanMove == 1 && endSquareProtected == 0) //puts piece in danger
  {
    return 1;
  }

  return 0;
}

MoveListNode *AIHardMove(Player *player, Board *gameBoard)
{
  if (player->type == COMPUTER)
  {
    MoveList *possibleMoves = getAllPossibleMoves(player, gameBoard);
    if (!possibleMoves)
    {
      return NULL;
    }

    analyzeMoveList(possibleMoves, gameBoard);

    MoveListNode *current = possibleMoves->head;
    MoveListNode *next;

    int playerChecked = kingChecked(player->playerKing, gameBoard);

    if (playerChecked == 1)
    {
      while (current)
      {
        next = current->nextNode;
        if (movePutsKingOutOfCheck(current->startSquare, current->endSquare, gameBoard) == 1)
        {
          return current; //if the player is checked return the first move that will put them out of check (update this later to check for best move)
        }
        current = next;
      }
    }

    current = possibleMoves->head;
    next = NULL;

    double maxMoveValue = 0.0;

    for (int i = 0; i < possibleMoves->length && current; ++i)
    {
      next = current->nextNode;
      if (current->moveValue > maxMoveValue)
      {
        maxMoveValue = current->moveValue;
      }
      current = next;
    }

    time_t t;
    srand((unsigned)time(&t));

    if (maxMoveValue == 0.0) //if all the moves have the value of 0 (at start of the game). pick a random move
    {
      int selection = rand() % possibleMoves->length;
      current = possibleMoves->head;
      next = NULL;
      for (int i = 0; i < selection && current; ++i)
      {
        next = current->nextNode;
        current = next;
      }
      return current;
    }

    int numMaxValMoves = 0; //keep track of the number of max value moves
    current = possibleMoves->head;
    next = NULL;

    for (int i = 0; i < possibleMoves->length && current; ++i) //add best moves to list
    {
      next = current->nextNode;
      if (current->moveValue == maxMoveValue)
      {
        numMaxValMoves++;
      }
      current = next;
    }

    if (numMaxValMoves == 1) // if there is one best move
    {
      current = possibleMoves->head;
      next = NULL;
      for (int i = 0; i < possibleMoves->length && current; ++i)
      {
        next = current->nextNode;
        if (current->moveValue == maxMoveValue)
        {
          return current;
        }
        current = next;
      }
    }
    else
    {
      MoveList *bestMoves = createMoveList();
      current = possibleMoves->head;
      next = NULL;

      for (int i = 0; i < possibleMoves->length && current; ++i) // add all the best moves to the move list if there are multiple best moves
      {
        next = current->nextNode;

        if (current->moveValue == maxMoveValue)
        {
          appendMove(current->startSquare, current->endSquare, bestMoves, current->moveValue);
        }
        current = next;
      }

      deleteMoveList(possibleMoves);

      int selection = rand() % bestMoves->length;

      current = bestMoves->head;
      next = NULL;

      for (int i = 0; i < selection && current; ++i)
      {
        next = current->nextNode;
        current = next;
      }

      return current;
    }
  }
  return NULL;
}

MoveListNode *AImediummove(Player *player, Board *gameBoard)
{
  if (player->type == COMPUTER)
  {
    MoveList *moveset1 = getAllPossibleMoves(player, gameBoard);

    if (!moveset1)
    {
      return NULL;
    }

    MoveListNode *current = moveset1->head;
    MoveListNode *next;
    assert(current);

    //check first if there is a possiblity to put opponent's king in check, if so move then break
    for (int j = 0; j < (moveset1->length); j++)
    {
      next = current->nextNode;
      if (kingChecked(player->playerKing, gameBoard) == 1)
      {
        if (movePutsKingOutOfCheck(current->startSquare, current->endSquare, gameBoard) == 1)
        {
          return current;
        }
      }

      if (movePutsOpponentKingInCheck(current->startSquare->thisSquaresPiece, current->endSquare, gameBoard) == 1) //returns 1 when puts in check
      {
        //printf("hi3\n");
        //moveChessPiece(current->startSquare->thisSquaresPiece, current->endSquare, gameBoard);
        return current; //don't want more moves
      }
      current = next;
    }
    MoveList *moveset2 = createMoveList();
    current = moveset1->head;
    time_t t;
    int selection;
    srand((unsigned)time(&t));
    for (int i = 0; i < (moveset1->length); i++) //add all the moves to a new list if it will result in a capture
    {
      next = current->nextNode;
      if (current->endSquare->thisSquaresPiece != NULL)
      {
        if (checkValidMove(current->startSquare->thisSquaresPiece, current->endSquare, gameBoard) == 2)
        {
          appendMove(current->startSquare, current->endSquare, moveset2, 0); //moveValue isn't taken into account for the medium level AI
        }
      }
      current = next;
    }
    if (moveset2->length == 0) //if list is empty then just random from whole list
    {
      deleteMoveList(moveset2);
      //random from moveset1 list
      MoveListNode *currents = moveset1->head;
      MoveListNode *nexts;
      selection = rand() % (moveset1->length);
      for (int k = 0; k < selection; k++)
      {
        nexts = currents->nextNode;
        currents = nexts;
      }

      return currents;
    }
    else //if moves are in list randomize from there
    {
      deleteMoveList(moveset1);
      //random from moveset list
      MoveListNode *currents = moveset2->head;
      MoveListNode *nexts;
      selection = rand() % (moveset2->length);
      for (int k = 0; k < selection; k++)
      {
        nexts = currents->nextNode;
        currents = nexts;
      }

      return currents;
    }
  }
  return NULL;
}
/* computer for easy mode (to be implemented in future release) */
MoveListNode *AIeasymove(Player *player, Board *gameBoard)
{
  if (player->type == COMPUTER)
  {
    //random through movelist
    time_t t;
    int selection;
    srand((unsigned)time(&t));
    MoveList *moveset = getAllPossibleMoves(player, gameBoard);
    MoveListNode *current = moveset->head;
    MoveListNode *next;

    for (int j = 0; j < (moveset->length); j++) //prioritize king capture
    {
      next = current->nextNode;
      if (kingChecked(player->playerKing, gameBoard) == 1)
      {
        if (movePutsKingOutOfCheck(current->startSquare, current->endSquare, gameBoard) == 1 &&
            movePutsKingInCheck(current->startSquare, current->endSquare, gameBoard) == 0)
        {
          return current;
        }
      }

      if (movePutsOpponentKingInCheck(current->startSquare->thisSquaresPiece, current->endSquare, gameBoard) == 1 &&
          movePutsKingInCheck(current->startSquare, current->endSquare, gameBoard) == 0) //returns 1 when puts in check
      {
        moveChessPiece(current->startSquare->thisSquaresPiece, current->endSquare, gameBoard);
        return current; //don't keep looking for moves
      }
      current = next;
    }

    selection = rand() % (moveset->length);
    MoveListNode *currents = moveset->head;
    MoveListNode *nexts;
    for (int i = 0; i < selection; i++)
    {
      nexts = currents->nextNode;
      currents = nexts;
    }
    return currents;
  }
  return NULL;
}

int max(int a, int b)
{
  return a > b ? a : b;
}
