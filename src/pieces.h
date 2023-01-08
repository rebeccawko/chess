//Header file to represent the chess pieces
#ifndef __PIECES_H__
#define __PIECES_H__

#include "chessStructs.h"

ChessPiece *createChessPiece(Color color, ChessPieceType pieceType, Square *square); //allocate memory for chess piece

const Square *getPiecesSquare(const ChessPiece *piece); //return the square the piece is on

void deleteChessPiece(ChessPiece *piece); //deallocate the memory for a chess piece

int getPieceValue(const ChessPiece *piece); // return 100 for pawn, 900 for queen, etc

void moveChessPiece(ChessPiece *piece, Square *endSquare, Board *gameBoard);

int checkValidMove(const ChessPiece *piece, const Square *endSquare, const Board *gameBoard); //returns 1 if the move is valid, 0 if the move is invalid, 2 if move will result in a capture

MoveList *getValidMoves(const ChessPiece *piece, Board *GameBoard); //return a list of all the valid moves for a piece

int checkDestinationStatus(const ChessPiece *piece, const Square *destinationSquare); //return 1 if destination is unoccupied, 0 if destination has the opposite color piece on it, -1 if same color

int checkDiagonalBlock(const ChessPiece *piece, const Square *endSquare, const Board *gameBoard); //return 1 if a piece blocks diagonal movement, 0 if there is no block

int checkHorizontalBlock(const ChessPiece *piece, const Square *endSquare, const Board *gameBoard);

int checkVerticalBlock(const ChessPiece *piece, const Square *endSquare, const Board *gameBoard);

int validPawnDoubleStep(const ChessPiece *piece, const Board *chessBoard); //return 1 if a pawn can perform the double step 0 if it can not

int kingChecked(ChessPiece *piece, Board *chessBoard); //returns 1 if player's king is in check, 0 otherwise, pass in king as parameter

int kingCheckMate(ChessPiece *piece, Board *chessBoard); //returns 1 if player's king is in checkmate, 0 otherwise.

int movePutsKingOutOfCheck(Square *startSquare, Square *endSquare, Board *gameBoard); //returns 1 if move will put the king out of check

int movePutsKingInCheck(Square *startSquare, Square *endSquare, Board *gameBoard); //returns 1 if move will put the player's king in check

int validPawnPromotion(const ChessPiece *piece); //return 1 if pawn can be promoted 0 if it can not

void promotePawn(const ChessPiece *piece); //promote pawn to queen for now if validPawnPromotion returns 1

int validEnPassant(ChessPiece *piece, Square *endSquare, Board *gameBoard); //checks for valid en passant, returns 1 if valid 0 if invalid

void captureEnPassant(ChessPiece *piece, Square *endSquare, Board *gameBoard); //moves pawn to diagonal position and captures pawn that passed

int checkValidCastle(ChessPiece *piece, Square *endSquare, Board *gameBoard, int rev); //checks for valid castle, returns 1 if valid 0 if invalid

void performCastle(ChessPiece *piece, Square *endSquare, Board *gameBoard, int rev); //performs the castling special move

#endif
