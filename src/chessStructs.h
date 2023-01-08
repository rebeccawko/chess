//header file for struct and enum definitions
#ifndef __CHESSTRUCTS_H__
#define __CHESSTRUCTS_H__

typedef enum
{
  WHITE,
  BLACK
} Color; //color of the player and his pieces

typedef enum
{
  PLAY,
  DONE
} Status;

typedef struct ChessPlayer Player;

typedef struct ChessPieces ChessPiece;

typedef struct BoardSquare Square;
typedef struct GameBoard Board;

typedef struct MoveListStruct MoveList;
typedef struct MoveListNodeStruct MoveListNode;

/* Player Struct-Related Data Definitions */

typedef enum
{
  HUMAN,
  COMPUTER,
  NONE
} PlayerType;

struct ChessPlayer
{
  Color playerColor;
  PlayerType type; //if the player is a human or computer

  ChessPiece *playerKing; //pointer to the player's king

  int isInCheckmate;            //1 if in checkmate, 0 if not in checkmate, initilize to 0 when creating player
  ChessPiece *playerPieces[16]; //array of pointers to player's pieces
};

/* Square Struct-Related definitions*/

struct BoardSquare
{
  int xPos;
  int yPos;

  ChessPiece *thisSquaresPiece;
};

/* Chess Piece Struct-Related definitions */

typedef enum
{
  NOPIECE,
  PAWN,
  KNIGHT,
  BISHOP,
  ROOK,
  QUEEN,
  KING
} ChessPieceType;

struct ChessPieces
{
  Square *square;         //pointer to the square the piece is on
  Square *previousSquare; //pointer to the position the piece was on Last
  ChessPieceType Type;
  Color color; //color of the chess piece
};

/* MoveList Struct-Related definitions */

struct MoveListStruct
{ //struct for linked list
  MoveListNode *head;
  MoveListNode *tail;
  int length;
};

struct MoveListNodeStruct
{ //node for move linked list
  struct BoardSquare *startSquare;
  struct BoardSquare *endSquare;

  double moveValue; //for AI to determine which move to pick

  MoveListNode *nextNode;
  MoveList *list;
};

/* Board Struct Related definitions */

struct GameBoard
{
  Square *chessBoard[8][8]; //chess board where chessBoard[0][0] corresponds to A1 and chessBoard[7][7] corresponds to H8
  Color playerTurn;         //which player's turn it is
  Player *player1;
  Player *player2;
  Status gameStatus;
};

#endif
