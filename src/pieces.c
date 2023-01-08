#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "pieces.h"
#include "player.h"
#include "square.h"
#include "moveList.h"

ChessPiece *createChessPiece(Color color, ChessPieceType pieceType, Square *square) //In square, pass in the square from the board (ex board[0][0] will be the square on A1)
{
  ChessPiece *newPiece = malloc(sizeof(ChessPiece));

  newPiece->square = square;
  newPiece->color = color;
  newPiece->Type = pieceType;
  newPiece->previousSquare = NULL;

  square->thisSquaresPiece = newPiece;
  return newPiece;
}

void deleteChessPiece(ChessPiece *piece)
{
  assert(piece);
  piece->square = NULL;
  free(piece);
  piece = NULL;
}

const Square *getPiecesSquare(const ChessPiece *piece)
{
  assert(piece);
  return piece->square;
}

int getPieceValue(const ChessPiece *piece)
{
  int pieceValue;
  switch (piece->Type)
  {
  case PAWN:
    pieceValue = 100.0;
    break;
  case KNIGHT:
    pieceValue = 300.0;
    break;
  case BISHOP:
    pieceValue = 300.0;
    break;
  case ROOK:
    pieceValue = 500.0;
    break;
  case QUEEN:
    pieceValue = 900.0;
    break;
  case KING:
    pieceValue = 1000.0;
    break;
  case NOPIECE:
    pieceValue = -10000.0;
    break;
  }
  return pieceValue;
}
void moveChessPiece(ChessPiece *piece, Square *endSquare, Board *gameBoard)
{

  assert(piece);
  assert(endSquare);

  if (checkValidMove(piece, endSquare, gameBoard) == 1)
  {
    piece->square->thisSquaresPiece = NULL;
    endSquare->thisSquaresPiece = piece;
    piece->previousSquare = piece->square;
    piece->square = endSquare;
  }
  else if (checkValidMove(piece, endSquare, gameBoard) == 2) //if the move is a capture
  {
    piece->square->thisSquaresPiece = NULL;

    Player *player;
    if (piece->color == WHITE)
    {
      player = gameBoard->player2;
    }
    else
    {
      player = gameBoard->player1;
    }

    deletePlayerPiece(endSquare->thisSquaresPiece, player);
    endSquare->thisSquaresPiece = piece;
    piece->previousSquare = piece->square;
    piece->square = endSquare;
  }
}

int checkDestinationStatus(const ChessPiece *piece, const Square *destination)
{
  assert(piece);
  assert(destination);
  if (destination->thisSquaresPiece == NULL)
  {
    return 1;
  } //destination has no piece
  else if (destination->thisSquaresPiece->color == piece->color)
  {
    return -1;
  } //destination has the piece of the same color
  else if (abs(destination->thisSquaresPiece->color - piece->color) == 1)
  {
    return 0;
  } //destination has a piece with the opposite color
  else
  {
    return -2;
  }
}

int checkValidMove(const ChessPiece *piece, const Square *endSquare, const Board *chessBoard)
{
  if (checkDestinationStatus(piece, endSquare) == -1)
  {
    return 0;
  }

  int X[8] = {2, 1, -1, -2, -2, -1, 1, 2}; //possible relative positions a knight can move to
  int Y[8] = {1, 2, 2, 1, -1, -2, -2, -1};
  switch (piece->Type)
  {
  case PAWN:
    if (checkDestinationStatus(piece, endSquare) == 1) //if the end square is unoccupied
    {
      if ((((getSquareYPos(endSquare) - getSquareYPos(getPiecesSquare(piece))) == 2 && (piece->color == WHITE)) ||
           ((getSquareYPos(endSquare) - getSquareYPos(getPiecesSquare(piece))) == -2 && (piece->color == BLACK))) &&
          (getSquareXPos(endSquare) == getSquareXPos(getPiecesSquare(piece))))
      {
        return validPawnDoubleStep(piece, chessBoard);
      } //if its pawns first move and user wants to do a double step

      else if (((((getSquareYPos(endSquare) - getSquareYPos(getPiecesSquare(piece))) == 1) && (piece->color == WHITE)) ||
                (((getSquareYPos(endSquare) - getSquareYPos(getPiecesSquare(piece))) == -1) && (piece->color == BLACK))) &&
               (getSquareXPos(endSquare) == getSquareXPos(getPiecesSquare(piece))))
      {
        return 1;
      }
    }
    else if (checkDestinationStatus(piece, endSquare) == 0) //if it's a diagonal  pawn capture
    {
      if (((((getSquareYPos(endSquare) - getSquareYPos(getPiecesSquare(piece))) == 1) && (piece->color == WHITE)) ||
           (((getSquareYPos(endSquare) - getSquareYPos(getPiecesSquare(piece))) == -1) && (piece->color == BLACK))) &&
          (abs(getSquareXPos(endSquare) - getSquareXPos(getPiecesSquare(piece))) == 1))
      {
        return 2;
      }
    }
    return 0;
    break;

  case KNIGHT:

    if (checkDestinationStatus(piece, endSquare) != -1) //if the end square does not have a piece of the same color as the piece being moved
    {
      for (int i = 0; i < 8; ++i)
      {
        if (getSquareXPos(endSquare) == getSquareXPos(getPiecesSquare(piece)) + X[i] && getSquareYPos(endSquare) == getSquareYPos(getPiecesSquare(piece)) + Y[i])
        {
          if (checkDestinationStatus(piece, endSquare) == 0)
          {
            return 2;
          }
          else
          {
            return 1;
          }
        }
      }
    }
    return 0;
    break;

  case BISHOP:
    if (checkDestinationStatus(piece, endSquare) != -1 && checkDiagonalBlock(piece, endSquare, chessBoard) == 0)
    {
      if (abs(getSquareXPos(endSquare) - getSquareXPos(getPiecesSquare(piece))) == abs(getSquareYPos(endSquare) - getSquareYPos(getPiecesSquare(piece)))) //check for diagonal movement
      {
        if (checkDestinationStatus(piece, endSquare) == 0)
        {
          return 2;
        }
        else
        {
          return 1;
        }
      }
    }
    return 0;
    break;

  case ROOK:
    if (checkDestinationStatus(piece, endSquare) != -1)
    {
      if ((getSquareXPos(getPiecesSquare(piece)) == getSquareXPos(endSquare)) && (getSquareYPos(getPiecesSquare(piece)) != getSquareYPos(endSquare))) //check for vertical movement
      {
        if (checkVerticalBlock(piece, endSquare, chessBoard) == 0) //check no vertical block
        {
          if (checkDestinationStatus(piece, endSquare) == 0) //find if its a capture
            return 2;
          else
            return 1;
        }
      }
      else if ((getSquareXPos(getPiecesSquare(piece)) != getSquareXPos(endSquare)) && (getSquareYPos(getPiecesSquare(piece)) == getSquareYPos(endSquare))) //check for horizontal movement
      {
        if (checkHorizontalBlock(piece, endSquare, chessBoard) == 0) //check no horizontal block
        {
          if (checkDestinationStatus(piece, endSquare) == 0) //find if its a capture
            return 2;
          else
            return 1;
        }
      }
    }

    return 0;
    break;

  case QUEEN:
    if (checkDestinationStatus(piece, endSquare) != -1)
    {
      if ((getSquareXPos(getPiecesSquare(piece)) == getSquareXPos(endSquare)) && (getSquareYPos(getPiecesSquare(piece)) != getSquareYPos(endSquare))) //check for vertical movement
      {
        if (checkVerticalBlock(piece, endSquare, chessBoard) == 0) //check no vertical block
        {
          if (checkDestinationStatus(piece, endSquare) == 0) //find if its a capture
            return 2;
          else
            return 1;
        }
      }
      else if ((getSquareXPos(getPiecesSquare(piece)) != getSquareXPos(endSquare)) && (getSquareYPos(getPiecesSquare(piece)) == getSquareYPos(endSquare))) //check for horizontal movement
      {
        if (checkHorizontalBlock(piece, endSquare, chessBoard) == 0) //check no horizontal block
        {
          if (checkDestinationStatus(piece, endSquare) == 0) //find if its a capture
            return 2;
          else
            return 1;
        }
      }
      else if (abs(getSquareXPos(endSquare) - getSquareXPos(getPiecesSquare(piece))) == abs(getSquareYPos(endSquare) - getSquareYPos(getPiecesSquare(piece)))) //check for diagonal movement
      {
        if (checkDiagonalBlock(piece, endSquare, chessBoard) == 0) //check no diagonal block
        {
          if (checkDestinationStatus(piece, endSquare) == 0) //find if its a capture
            return 2;
          else
            return 1;
        }
      }
    }
    return 0;
    break;

  case KING:
    if (checkDestinationStatus(piece, endSquare) != -1)
    {
      if (abs(getSquareXPos(endSquare) - getSquareXPos(getPiecesSquare(piece))) <= 1 && abs(getSquareYPos(endSquare) - getSquareYPos(getPiecesSquare(piece))) <= 1) //check for one space  in any direction
      {
        if (checkDestinationStatus(piece, endSquare) == 0)
        {
          return 2;
        }

        else if (checkDestinationStatus(piece, endSquare) == 1)
        {
          return 1;
        }
      }
    }
    return 0;
    break;

  case NOPIECE:
    return -2; //input error
    break;
  }
  return -2;
}

int checkHorizontalBlock(const ChessPiece *piece, const Square *endSquare, const Board *gameBoard)
{
  if (getSquareXPos(endSquare) > getSquareXPos(getPiecesSquare(piece)))
  {
    int y = getSquareYPos(getPiecesSquare(piece));
    for (int i = getSquareXPos(getPiecesSquare(piece)) + 1; i < getSquareXPos(endSquare); ++i)
    {
      if (checkDestinationStatus(piece, gameBoard->chessBoard[i][y]) != 1) // if the square at this spot in the board is not NULL (contains a piece)
      {
        return 1;
      }
    }
    return 0;
  }
  else if (getSquareXPos(endSquare) < getSquareXPos(getPiecesSquare(piece)))
  {
    int y = getSquareYPos(getPiecesSquare(piece));
    for (int i = getSquareXPos(getPiecesSquare(piece)) - 1; i > getSquareXPos(endSquare); --i)
    {
      if (checkDestinationStatus(piece, gameBoard->chessBoard[i][y]) != 1) // if the square at this spot in the board is not NULL
      {
        return 1;
      }
    }
    return 0;
  }
  else
  {
    return -1; //error in input to function
  }
}

int checkVerticalBlock(const ChessPiece *piece, const Square *endSquare, const Board *gameBoard)
{
  if (getSquareYPos(endSquare) > getSquareYPos(getPiecesSquare(piece)))
  {
    int x = getSquareXPos(getPiecesSquare(piece));

    for (int i = getSquareYPos(getPiecesSquare(piece)) + 1; i < getSquareYPos(endSquare); ++i)
    {
      if (checkDestinationStatus(piece, gameBoard->chessBoard[x][i]) != 1) // if the square at this spot in the board is not NULL (contains a piece)
      {
        return 1;
      }
    }

    return 0;
  }
  else if (getSquareYPos(endSquare) < getSquareYPos(getPiecesSquare(piece)))
  {
    int x = getSquareXPos(getPiecesSquare(piece));

    for (int i = getSquareYPos(getPiecesSquare(piece)) - 1; i > getSquareYPos(endSquare); --i)
    {
      if (checkDestinationStatus(piece, gameBoard->chessBoard[x][i]) != 1) // if the square at this spot in the board is not NULL
      {
        return 1;
      }
    }

    return 0;
  }
  else
  {
    return -1; //error in input to function
  }
}

int checkDiagonalBlock(const ChessPiece *piece, const Square *endSquare, const Board *gameBoard)
{
  enum directions
  {
    TOPLEFT,
    BOTTOMLEFT,
    TOPRIGHT,
    BOTTOMRIGHT
  };

  int direction;
  /*Check the direciton of the movement from the piece to the endSquare */
  if ((getSquareXPos(getPiecesSquare(piece)) < getSquareXPos(endSquare)) && (getSquareYPos(getPiecesSquare(piece)) < getSquareYPos(endSquare)))
    direction = TOPRIGHT;
  else if ((getSquareXPos(getPiecesSquare(piece)) < getSquareXPos(endSquare)) && (getSquareYPos(getPiecesSquare(piece)) > getSquareYPos(endSquare)))
    direction = BOTTOMRIGHT;
  else if ((getSquareXPos(getPiecesSquare(piece)) > getSquareXPos(endSquare)) && (getSquareYPos(getPiecesSquare(piece)) < getSquareYPos(endSquare)))
    direction = TOPLEFT;
  else if ((getSquareXPos(getPiecesSquare(piece)) > getSquareXPos(endSquare)) && (getSquareYPos(getPiecesSquare(piece)) > getSquareYPos(endSquare)))
    direction = BOTTOMLEFT;
  else
    return -1; //error in input to function

  int pieceX = getSquareXPos(getPiecesSquare(piece)), pieceY = getSquareYPos(getPiecesSquare(piece));
  int squareX = getSquareXPos(endSquare);

  switch (direction)
  {
  case TOPRIGHT:
    for (int i = 0; i < abs(squareX - pieceX) - 1; ++i)
    {
      if (checkDestinationStatus(piece, gameBoard->chessBoard[pieceX + 1 + i][pieceY + 1 + i]) != 1)
      {
        return 1;
      }
    }
    return 0;
    break;

  case BOTTOMRIGHT:
    for (int i = 0; i < abs(squareX - pieceX) - 1; ++i)
    {
      if (checkDestinationStatus(piece, gameBoard->chessBoard[pieceX + 1 + i][pieceY - 1 - i]) != 1)
      {
        return 1;
      }
    }
    return 0;
    break;

  case TOPLEFT:
    for (int i = 0; i < abs(squareX - pieceX) - 1; ++i)
    {
      if (checkDestinationStatus(piece, gameBoard->chessBoard[pieceX - 1 - i][pieceY + 1 + i]) != 1)
      {
        return 1;
      }
    }
    return 0;
    break;

  case BOTTOMLEFT:
    for (int i = 0; i < abs(squareX - pieceX) - 1; ++i)
    {
      if (checkDestinationStatus(piece, gameBoard->chessBoard[pieceX - 1 - i][pieceY - 1 - i]) != 1)
      {
        return 1;
      }
    }
    return 0;
    break;
  }
  return -1; //error in input to function
}

int validPawnDoubleStep(const ChessPiece *piece, const Board *chessBoard)
{
  if (piece->color == WHITE && getSquareYPos(piece->square) == 1)
  {
    if (getChessPiece(chessBoard->chessBoard[getSquareXPos(getPiecesSquare(piece))][3]) == NULL)
    {
      if (getChessPiece(chessBoard->chessBoard[getSquareXPos(getPiecesSquare(piece))][2]) == NULL)
      {
        return 1;
      }
    }
  }
  else if (piece->color == BLACK && getSquareYPos(piece->square) == 6)
  {
    if (getChessPiece(chessBoard->chessBoard[getSquareXPos(getPiecesSquare(piece))][4]) == NULL)
    {
      if (getChessPiece(chessBoard->chessBoard[getSquareXPos(getPiecesSquare(piece))][5]) == NULL)
      {
        return 1;
      }
    }
  }
  return 0;
}

int validPawnPromotion(const ChessPiece *piece)
{
  if (piece->color == WHITE && getSquareYPos(piece->square) == 7 && piece->Type == PAWN)
  {
    return 1;
  }
  else if (piece->color == BLACK && getSquareYPos(piece->square) == 0 && piece->Type == PAWN)
  {
    return 1;
  }

  return 0;
}

int kingChecked(ChessPiece *piece, Board *chessBoard) //pass in a king piece and the game board
{
  assert(piece);
  assert(chessBoard);

  if (piece->Type != KING)
  {
    return -2; //error in piece type input
  }

  Player *opponent;

  if ((piece->color == WHITE && chessBoard->player1->playerColor == WHITE) || (piece->color == BLACK && chessBoard->player1->playerColor == BLACK)) //find the opponent's color
  {
    opponent = chessBoard->player2;
  }
  else if ((piece->color == WHITE && chessBoard->player2->playerColor == WHITE) || (piece->color == BLACK && chessBoard->player2->playerColor == BLACK))
  {
    opponent = chessBoard->player1;
  }

  for (int i = 0; i < sizeof(opponent->playerPieces) / sizeof(opponent->playerPieces[0]); ++i)
  {
    if (opponent->playerPieces[i] == NULL || opponent->playerPieces[i]->square == NULL)
    {
      continue;
    }
    else if (checkValidMove(opponent->playerPieces[i], piece->square, chessBoard) != 0)
    {
      return 1;
    }
  }
  return 0;
}

int kingCheckMate(ChessPiece *piece, Board *chessBoard)
{
  if (piece->Type != KING)
  {
    return -2; //error in input to function
  }

  if (kingChecked(piece, chessBoard) == 0)
  {
    return 0;
  }

  if (kingChecked(piece, chessBoard) == 1)
  {
    Player *player;
    if ((piece->color == WHITE && chessBoard->player1->playerColor == WHITE) || (piece->color == BLACK && chessBoard->player1->playerColor == BLACK)) //find the player's color
    {
      player = chessBoard->player1;
    }
    else if ((piece->color == WHITE && chessBoard->player2->playerColor == WHITE) || (piece->color == BLACK && chessBoard->player2->playerColor == BLACK))
    {
      player = chessBoard->player2;
    }
    MoveList *possibleMoves = getAllPossibleMoves(player, chessBoard);
    MoveListNode *current = possibleMoves->head, *next;

    for (int i = 0; i < possibleMoves->length; ++i)
    {
      next = current->nextNode;
      if (movePutsKingOutOfCheck(current->startSquare, current->endSquare, chessBoard) == 1)
      {
        deleteMoveList(possibleMoves);
        player->isInCheckmate = 0;
        return 0;
      }
      current = next;
    }

    return 1;
    player->isInCheckmate = 1;
    deleteMoveList(possibleMoves);
    return 1; //king is in checkmate
  }
  return 0;
}

int movePutsKingOutOfCheck(Square *startSquare, Square *endSquare, Board *gameBoard)
{

  ChessPiece *piece = startSquare->thisSquaresPiece;
  ChessPiece *originalEndSquarePiece; //keep track of the piece that was on the end square before trying the move

  if (checkValidMove(piece, endSquare, gameBoard) == 0)
  {
    return 0;
  }

  ChessPiece *playerKing = getPlayerKing(piece, gameBoard);

  if (endSquare->thisSquaresPiece != NULL)
  {
    originalEndSquarePiece = endSquare->thisSquaresPiece;
  }
  else
  {
    originalEndSquarePiece = NULL;
  }

  int rVal = checkValidMove(piece, endSquare, gameBoard);
  int attackIndex; //index in playerPieces array of piece putting the king in check
  Player *opponent;
  if (rVal >= 0)
  {

    /* temporarily put the piece at the end square, updates state of gameboard*/
    piece->square->thisSquaresPiece = NULL;
    if (rVal == 2) //if the move is a capture, take the piece out of the opponent's player pieces array
    {

      if ((piece->color == WHITE && gameBoard->player1->playerColor == WHITE) || (piece->color == BLACK && gameBoard->player1->playerColor == BLACK)) //find the opponent's color
      {
        opponent = gameBoard->player2;
      }
      else if ((piece->color == WHITE && gameBoard->player2->playerColor == WHITE) || (piece->color == BLACK && gameBoard->player2->playerColor == BLACK))
      {
        opponent = gameBoard->player1;
      }

      for (int i = 0; i < (sizeof(opponent->playerPieces)) / sizeof(opponent->playerPieces[0]); i++)
      {
        if (opponent->playerPieces[i] == originalEndSquarePiece)
        {
          opponent->playerPieces[i] = NULL;
          attackIndex = i;
        }
      }
    }
    endSquare->thisSquaresPiece = piece; //update state of the gameboard with the move
    piece->square = endSquare;

    if (kingChecked(playerKing, gameBoard) == 0)
    {
      /* Move the piece back to the right place */
      piece->square = startSquare;
      startSquare->thisSquaresPiece = piece;
      endSquare->thisSquaresPiece = originalEndSquarePiece;
      if (rVal == 2) // add the piece back to the opponent's playerPieces array
      {
        opponent->playerPieces[attackIndex] = originalEndSquarePiece;
      }
      return 1;
    }
  }
  piece->square = startSquare; //move the piece back to the right place
  startSquare->thisSquaresPiece = piece;
  endSquare->thisSquaresPiece = originalEndSquarePiece;
  if (rVal == 2)
  {
    for (int i = 0; i < (sizeof(opponent->playerPieces)) / sizeof(opponent->playerPieces[0]); i++)
    {
      if (i == attackIndex)
        opponent->playerPieces[i] = originalEndSquarePiece;
    }
  }
  return 0;
}

int movePutsKingInCheck(Square *startSquare, Square *endSquare, Board *gameBoard) //returns 1 if the move will put the player in check (move is invalid), 0 if it will not be put into check
{
  ChessPiece *piece = startSquare->thisSquaresPiece;
  ChessPiece *originalEndSquarePiece; //keep track of the piece that was on the end square before trying the move
  if (checkValidMove(piece, endSquare, gameBoard) == 0)
  {
    return 0;
  }

  ChessPiece *playerKing = getPlayerKing(piece, gameBoard);

  if (endSquare->thisSquaresPiece != NULL)
  {
    originalEndSquarePiece = endSquare->thisSquaresPiece;
  }
  else
  {
    originalEndSquarePiece = NULL;
  }

  int rVal = checkValidMove(piece, endSquare, gameBoard);
  int attackIndex; //index in playerPieces array of piece putting the king in check
  Player *opponent;

  if (rVal == 2) //if the move is a capture, take the piece out of the opponent's player pieces array
  {

    if ((piece->color == WHITE && gameBoard->player1->playerColor == WHITE) || (piece->color == BLACK && gameBoard->player1->playerColor == BLACK)) //find the opponent's color
    {
      opponent = gameBoard->player2;
    }
    else if ((piece->color == WHITE && gameBoard->player2->playerColor == WHITE) || (piece->color == BLACK && gameBoard->player2->playerColor == BLACK))
    {
      opponent = gameBoard->player1;
    }

    for (int i = 0; i < (sizeof(opponent->playerPieces)) / sizeof(opponent->playerPieces[0]); i++)
    {
      if (opponent->playerPieces[i] == originalEndSquarePiece)
      {
        opponent->playerPieces[i] = NULL;
        attackIndex = i;
      }
    }
  }

  /* temporarily move the piece to the desired endsquare */
  piece->square->thisSquaresPiece = NULL;
  endSquare->thisSquaresPiece = piece;
  piece->square = endSquare;

  if (kingChecked(playerKing, gameBoard) == 1)
  {
    if (rVal == 2)
      opponent->playerPieces[attackIndex] = originalEndSquarePiece;
    /* move the piece back to the right place */
    piece->square = startSquare;
    startSquare->thisSquaresPiece = piece;
    endSquare->thisSquaresPiece = originalEndSquarePiece;
    return 1;
  }

  if (rVal == 2)
    opponent->playerPieces[attackIndex] = originalEndSquarePiece;
  piece->square = startSquare;
  startSquare->thisSquaresPiece = piece;
  endSquare->thisSquaresPiece = originalEndSquarePiece;
  return 0;
}

MoveList *getValidMoves(const ChessPiece *piece, Board *gameBoard)
{

  MoveList *newMoveList = createMoveList();

  for (int x = 0; x < 8; ++x)
  {
    for (int y = 0; y < 8; ++y)
    {
      if ((checkValidMove(piece, gameBoard->chessBoard[x][y], gameBoard) != 0))
      {
        double moveValue = 0.0;
        if (getChessPiece(gameBoard->chessBoard[x][y]))
        {
          switch (gameBoard->chessBoard[x][y]->thisSquaresPiece->Type)
          {
          case PAWN:
            moveValue = 100.0;
            break;
          case KNIGHT:
            moveValue = 300.0;
            break;
          case BISHOP:
            moveValue = 300.0;
            break;
          case ROOK:
            moveValue = 500.0;
            break;
          case QUEEN:
            moveValue = 900.0;
            break;
          case KING:
            moveValue = 1000.0;
            break;
          case NOPIECE:
            moveValue = -10000.0;
            break;
          }
        }
        if (movePutsKingInCheck(piece->square, gameBoard->chessBoard[x][y], gameBoard) == 0)
        {
          appendMove(piece->square, gameBoard->chessBoard[x][y], newMoveList, moveValue);
        }
      }
    }
  }

  return newMoveList;
}

int validEnPassant(ChessPiece *piece, Square *endSquare, Board *gameBoard)
{
  if (piece->Type != PAWN)
  {
    return 0;
  }

  if (getChessPiece(endSquare) == NULL) //checking if end square is empty
  {
    if (abs(getSquareXPos(endSquare) - getSquareXPos(getPiecesSquare(piece))) == 1 && abs(getSquareYPos(endSquare) - getSquareYPos(getPiecesSquare(piece))) == 1) //check diagonal movement
    {
      if (piece->color == WHITE)
      {
        ChessPiece *tempPiece = getChessPiece(gameBoard->chessBoard[getSquareXPos(endSquare)][getSquareYPos(endSquare) - 1]); //piece getting captured
        if (tempPiece->color == BLACK && tempPiece->Type == PAWN)
        {
          if (getSquareYPos(tempPiece->previousSquare) == 6 && getSquareYPos(tempPiece->square) == 4)
          {
            return 1;
          }
        }
      }
      else if (piece->color == BLACK)
      {
        ChessPiece *tempPiece = getChessPiece(gameBoard->chessBoard[getSquareXPos(endSquare)][getSquareYPos(endSquare) + 1]); //piece getting captured
        if (tempPiece->color == WHITE && tempPiece->Type == PAWN)
        {
          if (getSquareYPos(tempPiece->previousSquare) == 1 && getSquareYPos(tempPiece->square) == 3)
          {
            return 1;
          }
        }
      }
    }
  }
  return 0;
}

void captureEnPassant(ChessPiece *piece, Square *endSquare, Board *gameBoard)
{
  if (validEnPassant(piece, endSquare, gameBoard) != 1)
  {
    return;
  }
  Player *player;
  if (piece->color == WHITE)
  {
    player = gameBoard->player2;
  }
  else
  {
    player = gameBoard->player1;
  }

  //move pawn diagonally to chosen square
  piece->square->thisSquaresPiece = NULL;
  endSquare->thisSquaresPiece = piece;
  piece->previousSquare = piece->square;
  piece->square = endSquare;

  if (piece->color == WHITE) //deletes/captures other pawn that just double stepped
  {
    ChessPiece *tempPiece = getChessPiece(gameBoard->chessBoard[getSquareXPos(endSquare)][getSquareYPos(endSquare) - 1]);
    deletePlayerPiece(tempPiece, player);
  }
  else if (piece->color == BLACK)
  {
    ChessPiece *tempPiece = getChessPiece(gameBoard->chessBoard[getSquareXPos(endSquare)][getSquareYPos(endSquare) + 1]);
    deletePlayerPiece(tempPiece, player);
  }
}

/* piece is the King, endSquare is 2 squares away from king for a valid castle, gameBoard is the chess board*/
int checkValidCastle(ChessPiece *piece, Square *endSquare, Board *gameBoard, int rev)
{
  if (piece->Type != KING) // if the piece is not a king castling is invalid
  {
    return 0;
  }

  if (getSquareYPos(getPiecesSquare(piece)) != getSquareYPos(endSquare)) //make sure end square y position is the same as the king
  {
    return 0;
  }

  if (getSquareXPos(getPiecesSquare(piece)) == 4 || (rev == 1 && getSquareXPos(getPiecesSquare(piece)) == 3)) //check the king is in initial position and they click the empty square next to the rook
  {
    if (getSquareXPos(endSquare) == 6 || (rev == 1 && getSquareXPos(endSquare) == 5)) //CHECK CASTLE WITH ROOK ON FILE H
    {
      if (piece->color == WHITE && getChessPiece(gameBoard->chessBoard[7][0])->Type == ROOK && getChessPiece(gameBoard->chessBoard[7][0])->color == WHITE) //check white castle
      {
        if (checkHorizontalBlock(piece, gameBoard->chessBoard[7][0], gameBoard) == 0) //make sure no piece is between king and rook on rank 1
        {
          return 1;
        }
      }
      else if (piece->color == BLACK && getChessPiece(gameBoard->chessBoard[7][7])->Type == ROOK && getChessPiece(gameBoard->chessBoard[7][7])->color == BLACK) //check black castle
      {
        if (checkHorizontalBlock(piece, gameBoard->chessBoard[7][7], gameBoard) == 0) //make sure no piece is between king and rook on rank 8
        {
          return 1;
        }
      }
      return 0;
    }
    else if (getSquareXPos(endSquare) == 2 || (rev == 1 && getSquareXPos(endSquare) == 1)) //CHECK CASTLE WITH ROOK ON FILE A
    {
      if (piece->color == WHITE && getChessPiece(gameBoard->chessBoard[0][0])->Type == ROOK && getChessPiece(gameBoard->chessBoard[0][0])->color == WHITE) //check white castle
      {
        if (checkHorizontalBlock(piece, gameBoard->chessBoard[0][0], gameBoard) == 0) //make sure no piece is between king and rook on rank 1
        {
          return 2;
        }
      }
      else if (piece->color == BLACK && getChessPiece(gameBoard->chessBoard[0][7])->Type == ROOK && getChessPiece(gameBoard->chessBoard[0][7])->color == BLACK) //check black castle
      {
        if (checkHorizontalBlock(piece, gameBoard->chessBoard[0][7], gameBoard) == 0) // make sure no piece is between king and rook on rank 8
        {
          return 2;
        }
      }
      return 0;
    }
  }
  return 0;
}

/* User must click 2 squares away from the king for a castle */
void performCastle(ChessPiece *piece, Square *endSquare, Board *gameBoard, int rev)
{
  assert(piece);
  assert(endSquare);
  assert(gameBoard);

  if (checkValidCastle(piece, endSquare, gameBoard, rev) != 0)
  {
    if (getSquareXPos(endSquare) > getSquareXPos(getPiecesSquare(piece))) //if the castle is with rook on file H
    {
      if (piece->color == WHITE)
      {
        ChessPiece *rookCastle = getChessPiece(gameBoard->chessBoard[7][0]);
        /* Move the rook to the correct space*/
        rookCastle->square->thisSquaresPiece = NULL;
        if (rev == 0)
        {
          gameBoard->chessBoard[5][0]->thisSquaresPiece = rookCastle;
          rookCastle->square = gameBoard->chessBoard[5][0];
        }
        else if (rev == 1)
        {
          gameBoard->chessBoard[4][0]->thisSquaresPiece = rookCastle;
          rookCastle->square = gameBoard->chessBoard[4][0];
        }
      }
      else if (piece->color == BLACK)
      {
        ChessPiece *rookCastle = getChessPiece(gameBoard->chessBoard[7][7]);
        /* Move the rook to the correct space*/
        rookCastle->square->thisSquaresPiece = NULL;
        if (rev == 0)
        {
          gameBoard->chessBoard[5][7]->thisSquaresPiece = rookCastle;
          rookCastle->square = gameBoard->chessBoard[5][7];
        }
        else if (rev == 1)
        {
          gameBoard->chessBoard[4][7]->thisSquaresPiece = rookCastle;
          rookCastle->square = gameBoard->chessBoard[4][7];
        }
      }
    }
    else if (getSquareXPos(getPiecesSquare(piece)) > getSquareXPos(endSquare)) //uf castle is with rook on file A
    {
      if (piece->color == WHITE)
      {
        ChessPiece *rookCastle = getChessPiece(gameBoard->chessBoard[0][0]);
        /* Move the rook to the correct space*/
        rookCastle->square->thisSquaresPiece = NULL;
        if (rev == 0)
        {
          gameBoard->chessBoard[3][0]->thisSquaresPiece = rookCastle;
          rookCastle->square = gameBoard->chessBoard[3][0];
        }
        else if (rev == 1)
        {
          gameBoard->chessBoard[2][0]->thisSquaresPiece = rookCastle;
          rookCastle->square = gameBoard->chessBoard[2][0];
        }
      }
      else if (piece->color == BLACK)
      {
        ChessPiece *rookCastle = getChessPiece(gameBoard->chessBoard[0][7]);
        /* Move the rook to the correct space*/
        rookCastle->square->thisSquaresPiece = NULL;
        if (rev == 0)
        {
          gameBoard->chessBoard[3][7]->thisSquaresPiece = rookCastle;
          rookCastle->square = gameBoard->chessBoard[3][7];
        }
        else if (rev == 1)
        {
          gameBoard->chessBoard[2][7]->thisSquaresPiece = rookCastle;
          rookCastle->square = gameBoard->chessBoard[2][7];
        }
      }
    }
    /* moves the king to the end square*/
    piece->square->thisSquaresPiece = NULL;
    endSquare->thisSquaresPiece = piece;
    piece->square = endSquare;
  }
}
