//header file to represent chess player

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "chessStructs.h"

Player *createPlayer(Color color, PlayerType type);

void deletePlayer(Player *player);

void deletePlayerPiece(ChessPiece *piece, Player *player);

void fillPlayerPieces(Player *player, Board *gameBoard); //after populating the gameboard with the pieces, set the pieces to the player that owns them

int playerCheck(Player *player); //returns 1 if player's king is in check, 0 otherwise

int playerCheckMate(Player *player); //returns 1 if player's king is in checkmate, 0 otherwise.

MoveList *getAllPossibleMoves(Player *player, Board *gameBoard); //return a list of all of a player's valid moves

ChessPiece *getOpponentPlayerKing(ChessPiece *piece, Board *gameBoard); //returns the opponent player's king

ChessPiece *getPlayerKing(ChessPiece *piece, Board *gameBoard); //returns pointer to the player's king when you pass a piece into it

int movePutsOpponentKingInCheck(ChessPiece *piece, Square *endSquare, Board *gameBoard); //for chess AI to check to see if a move will put the opponent's king in check, 1 if true, 0 if false

int movePutsPieceInDanger(ChessPiece *piece, Square *endSquare, Board *gameBoard); //for chess AI, checks to see if move will put piece in unprotected square

int max(int a, int b); // helper function to find max of two numbers (used for linked list lengths)

MoveListNode *AIHardMove(Player *player, Board *gameBoard);

MoveListNode *AImediummove(Player *player, Board *gameBoard);

MoveListNode *AIeasymove(Player *player, Board *gameBoard);

#endif