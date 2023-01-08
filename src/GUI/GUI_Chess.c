/***********************************************************
*
*A simple GTK example
*simple.c: show a 2x2 board and move the king by clicking
*author: Weiwei Chen
*initial version: 01/22/13 EECS22L Winter 2013
*
***********************************************************/

#include <gtk/gtk.h>
#include <stdlib.h>
#include <assert.h>
#include "GUI_Chess.h"
#include "../pieces.h"
#include "string.h"
#include "main-menu.h"
#include "../chessStructs.h"
#include "../board.h"
#include "../square.h"
#include "../player.h"
#include "../moveList.h"
#include "../../network/chessClient.h"

/*Global Variables */
FILE *mLog;
int opp;
int set;
int cpuDiff;
gint len = -1;
const char *newline = "\n";

GtkWidget *window;
GtkWidget *fixed;
GtkWidget *chess_icon;
GtkWidget *table;

GtkWidget *promWin;
ChessPieceType *promoted;

GtkWidget *hisWin;
GtkWidget *scrollView;
GtkWidget *moveHistory;
GtkTextBuffer *history;
GtkTextIter iter;
GtkTextMark *update;

GtkWidget *chatwin;
GtkWidget *chatbox;
GtkWidget *sendbutton;   
GtkWidget *chatTable;
GtkWidget *chatentry;
GtkWidget *chatscrollView;
GtkTextBuffer *chathistory;
GtkTextMark *autoscroll;

//enum is a user defined data type assigns names to integral constants
//enum is defined in the header file
//enum variable is GRID
//Board is an object of GRID instantiated below
//Black corresponds to 0 white to 1 and king to 2
enum GRID Game[9][9];
//variable Board[][] of type enum boolean is created
void MoveThePiece(int g_x, int g_y, int oldX, int oldY, Board *gameBoard);
void DrawBoard();

void InitBoard(Player *player2, Board *thisGameBoard)
{
  int i, j;
  for (i = 0; i < 8; i++)
  {
    for (j = 0; j < 8; j++)
    {
      if ((i + j) % 2 == 0)
      {
        Game[i][j] = SWHITE;
      }
      else
      {
        Game[i][j] = SBLACK;
      }
    }
  }

  if (set == 0)
  {
    Game[0][0] = BROOK;
    Game[1][0] = BKNIGHT;
    Game[2][0] = BBISHOP;
    Game[3][0] = BQUEEN;
    Game[4][0] = BKING;
    Game[5][0] = BBISHOP;
    Game[6][0] = BKNIGHT;
    Game[7][0] = BROOK;
    Game[0][1] = BPAWN;
    Game[1][1] = BPAWN;
    Game[2][1] = BPAWN;
    Game[3][1] = BPAWN;
    Game[4][1] = BPAWN;
    Game[5][1] = BPAWN;
    Game[6][1] = BPAWN;
    Game[7][1] = BPAWN;

    Game[0][7] = WROOK;
    Game[1][7] = WKNIGHT;
    Game[2][7] = WBISHOP;
    Game[3][7] = WQUEEN;
    Game[4][7] = WKING;
    Game[5][7] = WBISHOP;
    Game[6][7] = WKNIGHT;
    Game[7][7] = WROOK;
    Game[0][6] = WPAWN;
    Game[1][6] = WPAWN;
    Game[2][6] = WPAWN;
    Game[3][6] = WPAWN;
    Game[4][6] = WPAWN;
    Game[5][6] = WPAWN;
    Game[6][6] = WPAWN;
    Game[7][6] = WPAWN;

    Game[8][0] = eight;
    Game[8][1] = seven;
    Game[8][2] = six;
    Game[8][3] = five;
    Game[8][4] = four;
    Game[8][5] = three;
    Game[8][6] = two;
    Game[8][7] = one;
    Game[8][8] = SWHITE;
    Game[0][8] = a;
    Game[1][8] = b;
    Game[2][8] = c;
    Game[3][8] = d;
    Game[4][8] = e;
    Game[5][8] = f;
    Game[6][8] = g;
    Game[7][8] = h;
    if (opp == 1)
    {
      Game[8][8] = ai;
    }
    else
    {
      Game[8][8] = SWHITE;
    }
  }
  else
  {
    Game[0][7] = BROOK;
    Game[1][7] = BKNIGHT;
    Game[2][7] = BBISHOP;
    Game[3][7] = BKING;
    Game[4][7] = BQUEEN;
    Game[5][7] = BBISHOP;
    Game[6][7] = BKNIGHT;
    Game[7][7] = BROOK;
    Game[0][6] = BPAWN;
    Game[1][6] = BPAWN;
    Game[2][6] = BPAWN;
    Game[3][6] = BPAWN;
    Game[4][6] = BPAWN;
    Game[5][6] = BPAWN;
    Game[6][6] = BPAWN;
    Game[7][6] = BPAWN;

    Game[0][0] = WROOK;
    Game[1][0] = WKNIGHT;
    Game[2][0] = WBISHOP;
    Game[3][0] = WKING;
    Game[4][0] = WQUEEN;
    Game[5][0] = WBISHOP;
    Game[6][0] = WKNIGHT;
    Game[7][0] = WROOK;
    Game[0][1] = WPAWN;
    Game[1][1] = WPAWN;
    Game[2][1] = WPAWN;
    Game[3][1] = WPAWN;
    Game[4][1] = WPAWN;
    Game[5][1] = WPAWN;
    Game[6][1] = WPAWN;
    Game[7][1] = WPAWN;

    Game[8][0] = one;
    Game[8][1] = two;
    Game[8][2] = three;
    Game[8][3] = four;
    Game[8][4] = five;
    Game[8][5] = six;
    Game[8][6] = seven;
    Game[8][7] = eight;
    Game[8][8] = SWHITE;
    Game[0][8] = h;
    Game[1][8] = g;
    Game[2][8] = f;
    Game[3][8] = e;
    Game[4][8] = d;
    Game[5][8] = c;
    Game[6][8] = b;
    Game[7][8] = a;
    if (opp == 1)
    {
      Game[8][8] = ai;
    }
    else
    {
      Game[8][8] = SWHITE;
    }
  }
}

void removeThePiece(int x, int y)
{
  if ((x + y) % 2 == 0)
  {
    Game[x][y] = SWHITE;
  }
  else
  {
    Game[x][y] = SBLACK;
  }
}

char *numericToStandard(int c_x, int c_y) // not used
{
  char *g_x;
  int g_y;
  if (set == 0)
  {
    *g_x = 65 + c_x;
    g_y = g_y;
  }
  else
  {
    *g_x = 65 + c_x;
    g_y = 7 - g_y;
  }
  sprintf(g_x, "%s%d ->  %s%d", g_x, g_y);
  return g_x;
}

void ReverseGridColor(int g_x, int g_y)
{
  if (Game[g_x][g_y] == SBLACK)
  {
    Game[g_x][g_y] = SWHITE;
  }
  else
  {
    Game[g_x][g_y] = SBLACK;
  }
}

enum GRID promote(ChessPiece *piece, enum GRID GRID)
{
  // Pick Promotion Piece
  promWin = gtk_dialog_new_with_buttons("Promote Piece", GTK_WINDOW(window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, "Queen", QUEEN, "Rook", ROOK, "Knight", KNIGHT, "Bishop", BISHOP, NULL);
  gint result = gtk_dialog_run(GTK_DIALOG(promWin));
  switch (result)
  {
  case QUEEN:
    *promoted = QUEEN;
    break;
  case ROOK:
    *promoted = ROOK;
    break;
  case KNIGHT:
    *promoted = KNIGHT;
    break;
  case BISHOP:
    *promoted = BISHOP;
    break;
  }
  gtk_widget_destroy(promWin);

  switch (*promoted)
  {
  case QUEEN:
    if (GRID <= 13 && GRID >= 9)
    {
      GRID = WQUEEN;
    }
    else
    {
      GRID = BQUEEN;
    }
    break;
  case KNIGHT:
    if (GRID <= 13 && GRID >= 9)
    {
      GRID = WKNIGHT;
    }
    else
    {
      GRID = BKNIGHT;
    }
    break;
  case ROOK:
    if (GRID <= 13 && GRID >= 9)
    {
      GRID = WROOK;
    }
    else
    {
      GRID = BROOK;
    }
    break;
  case BISHOP:
    if (GRID <= 13 && GRID >= 9)
    {
      GRID = WBISHOP;
    }
    else
    {
      GRID = BBISHOP;
    }
    break;
  }

  piece->Type = *promoted;
  return GRID;
}

void MoveThePiece(int g_x, int g_y, int oldX, int oldY, Board *gameBoard)
{

  int rVal = -1; // move parameters: rVal for Valid Move, cVal for Valid Castling Move, eVal for Valid En Passant Capture
  int cVal = 0;
  int eVal = 0;

  //check valid move input parameters
  assert(gameBoard);
  assert(gameBoard->chessBoard);
  assert(gameBoard->chessBoard[oldX][7 - oldY]->thisSquaresPiece);

  ChessPiece *selectedPiece = gameBoard->chessBoard[oldX][7 - oldY]->thisSquaresPiece;
  Square *destinationSquare = gameBoard->chessBoard[g_x][7 - g_y];

  // initialize move parameters
  rVal = checkValidMove(selectedPiece, destinationSquare, gameBoard);
  cVal = checkValidCastle(selectedPiece, destinationSquare, gameBoard, set);
  eVal = validEnPassant(selectedPiece, destinationSquare, gameBoard);

  // check to see if your King piece is in Check
  ChessPiece *kingCheck = getPlayerKing(selectedPiece, gameBoard);
  int cFlag = 0;                                                                                            //check flag to see if king is currently in check
  int intoCFlag = movePutsKingInCheck(gameBoard->chessBoard[oldX][7 - oldY], destinationSquare, gameBoard); //check flag to see if move will put king in check

  if (intoCFlag == 1)
  {
    rVal = 0;
  }

  if (kingChecked(kingCheck, gameBoard) == 1)
  {
    if (movePutsKingOutOfCheck(selectedPiece->square, destinationSquare, gameBoard) == 1)
    {
      cFlag = 0;
    }
    else
    {
      cFlag = 1;
      rVal = 0;
    }
  }

  // Moving Functionality
  char move[SLEN];
  char toSend[SLEN];
  int gameOver = 0;
  if (((rVal != 0) || (cVal != 0) || (eVal != 0)) && (getGameTurn(gameBoard) == selectedPiece->color))
  {
    char *pie;
    char *cap = "";
    char *capPiece = "";
    char *castle = "";
    char *enPassant = "";
    if (rVal == 2)
    {
      if (destinationSquare->thisSquaresPiece->Type == KING)
      {
        gameOver == 1;
        if ((destinationSquare->thisSquaresPiece->color == 1 && set == 0) || (destinationSquare->thisSquaresPiece->color == 1 && set == 1))
        {
          gameOver = 1; //win case
        }
        else
        {
          gameOver = 2; //loss case
        }
      }
      moveChessPiece(selectedPiece, destinationSquare, gameBoard);

      cap = "CAPTURE\n";
    }
    else if (eVal == 1)
    {
      captureEnPassant(selectedPiece, destinationSquare, gameBoard);
      if (g_y == 2)
      {
        removeThePiece(g_x, g_y + 1);
      }
      else if (g_y == 5)
      {
        removeThePiece(g_x, g_y - 1);
      }

      enPassant = "EN PASSANT";
    }

    else if ((set == 0 && cVal == 1) || (set == 1 && cVal == 2))
    {
      if (set == 1)
      {
        performCastle(selectedPiece, destinationSquare, gameBoard, set);
        Game[2][g_y] = Game[0][oldY];
        removeThePiece(0, oldY);
      }
      else
      {
        performCastle(selectedPiece, destinationSquare, gameBoard, set);
        Game[5][g_y] = Game[7][oldY];
        removeThePiece(7, oldY);
      }

      castle = "CASTLE";
    }
    else if ((set == 0 && cVal == 2) || (set == 1 && cVal == 1))
    {

      if (set == 1)
      {
        performCastle(selectedPiece, destinationSquare, gameBoard, set);
        Game[4][g_y] = Game[7][oldY];
        removeThePiece(7, oldY);
      }
      else
      {
        performCastle(selectedPiece, destinationSquare, gameBoard, set);
        Game[3][g_y] = Game[0][oldY];
        removeThePiece(0, oldY);
      }
      castle = "CASTLE";
    }
    else
    {
      moveChessPiece(selectedPiece, destinationSquare, gameBoard);
    }
    Game[g_x][g_y] = Game[oldX][oldY];

    removeThePiece(oldX, oldY);

    // Check to see if move resulted in checkmate
    int x, y;
    if (gameOver != 1)
    {
      for (y = 0; y < 8; y++)
      {
        for (x = 0; x < 8; x++)
        {
          ChessPiece *kingCheck = NULL;
          if (gameBoard->chessBoard[x][y]->thisSquaresPiece != NULL)
          {
            if (gameBoard->chessBoard[x][y]->thisSquaresPiece->Type == KING)
            {
              kingCheck = gameBoard->chessBoard[x][y]->thisSquaresPiece;
              if (kingChecked(kingCheck, gameBoard) == 1)
              {
                gameOver = kingCheckMate(kingCheck, gameBoard);
                if (gameOver == 1)
                {
                  if ((kingCheck->color == 1 && set == 0) || (kingCheck->color == 1 && set == 1))
                  {
                    gameOver = 1; //win case
                  }
                  else
                  {
                    gameOver = 2; //loss case
                  }
                  break;
                }
              }
            }
          }
        }
        if (gameOver > 0)
        {
          break;
        }
      }
    }

    // History Log Messages
    switch (destinationSquare->thisSquaresPiece->Type)
    {
    case PAWN:
      pie = "PAWN";
      break;
    case ROOK:
      pie = "ROOK";
      break;
    case KNIGHT:
      pie = "KNIGHT";
      break;
    case BISHOP:
      pie = "BISHOP";
      break;
    case KING:
      pie = "KING";
      break;
    case QUEEN:
      pie = "QUEEN";
      break;
    }
    if ((set == 0 && getGameTurn(gameBoard) == WHITE) || (set == 1 && getGameTurn(gameBoard) == BLACK))
      sprintf(move, "WHITE %s %s %s\n(%d, %d) -> (%d, %d)\n%s", pie, castle, enPassant, oldX, 7 - oldY, g_x, 7 - g_y, cap);
    else
      sprintf(move, "BLACK %s %s %s\n(%d, %d) -> (%d, %d)\n%s", pie, castle, enPassant, oldX, 7 - oldY, g_x, 7 - g_y, cap);

    if (validPawnPromotion(destinationSquare->thisSquaresPiece) == 1)
    {
      Game[g_x][g_y] = promote(destinationSquare->thisSquaresPiece, Game[g_x][g_y]);
    }

    changeGameTurn(gameBoard);
  }
  else if ((rVal != 0) && (getGameTurn(gameBoard) != selectedPiece->color))
  {
    sprintf(move, "It's not your move.\n");
  }
  else if (rVal == 0)
  {
    if (cFlag == 1)
    {
      sprintf(move, "King in Check, try again.\n(%d, %d) -> (%d, %d)\n", oldX, 7 - oldY, g_x, 7 - g_y);
    }
    else if (intoCFlag == 1)
    {
      sprintf(move, "Move puts King in check, try again.\n(%d, %d) -> (%d, %d)\n", oldX, 7 - oldY, g_x, 7 - g_y);
    }
    else
    {
      sprintf(move, "Invalid Move, try again.\n(%d, %d) -> (%d, %d)\n", oldX, 7 - oldY, g_x, 7 - g_y);
    }
  }
  gtk_text_buffer_insert(history, &iter, move, -1);
  fputs(move, mLog);
  gtk_text_view_scroll_to_mark(GTK_TEXT_VIEW(moveHistory), gtk_text_buffer_get_insert(history), 0.0, TRUE, 0.5, 0.5);
  sprintf(toSend, "(%d, %d) -> (%d, %d)\n", oldX, 7 - oldY, g_x, 7 - g_y);
  char message[SLEN];
  strcpy(message, toSend);
  startClientConnection(15000, message);
  if (gameOver > 0)
  {
    char *msg;

    if (gameOver == 2)
    {
      msg = LOSS_MESSAGE;
    }
    else if (gameOver == 1)
    {
      msg = WIN_MESSAGE;
    }
    gtk_text_buffer_insert(history, &iter, msg, -1);
    fputs(msg, mLog);
    char endgame[SLEN];
    strcpy(endgame, msg);
    startClientConnection(15000, endgame);
    startClientConnection(15000, "shutdown");
    GtkWidget *quitWin = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_OTHER, GTK_BUTTONS_CLOSE, msg);
    gint result = gtk_dialog_run(GTK_DIALOG(quitWin));
    gtk_main_quit(); // Quit Game on Checkmate
    gtk_widget_destroy(quitWin);
  }
}

void DrawBoard() // Creates and Updates Visual Board
{
  int i, j;

  for (i = 0; i < 9; i++)
  {
    for (j = 0; j < 9; j++)
    {
      switch (Game[i][j])
      {
      case SBLACK:
        chess_icon = gtk_image_new_from_file("./chess_icon/Bsquare.jpg");
        break;
      case SWHITE:
        chess_icon = gtk_image_new_from_file("./chess_icon/Wsquare.jpg");
        break;
      case BKING:
        if ((i + j) % 2 == 0)
        {
          chess_icon = gtk_image_new_from_file("./chess_icon/bKoW.png");
        }
        else
        {
          chess_icon = gtk_image_new_from_file("./chess_icon/bKoB.png");
        }
        break;
      case BQUEEN:
        if ((i + j) % 2 == 0)
        {
          chess_icon = gtk_image_new_from_file("./chess_icon/bQoW.png");
        }
        else
        {
          chess_icon = gtk_image_new_from_file("./chess_icon/bQoB.png");
        }
        break;
      case BROOK:
        if ((i + j) % 2 == 0)
        {
          chess_icon = gtk_image_new_from_file("./chess_icon/bRoW.png");
        }
        else
        {
          chess_icon = gtk_image_new_from_file("./chess_icon/bRoB.png");
        }

        break;

      case BKNIGHT:
        if ((i + j) % 2 == 0)
        {
          chess_icon = gtk_image_new_from_file("./chess_icon/bNoW.png");
        }
        else
        {
          chess_icon = gtk_image_new_from_file("./chess_icon/bNoB.png");
        }
        break;

      case BPAWN:
        if ((i + j) % 2 == 0)
        {
          chess_icon = gtk_image_new_from_file("./chess_icon/bPoW.png");
        }
        else
        {
          chess_icon = gtk_image_new_from_file("./chess_icon/bPoB.png");
        }
        break;
      case BBISHOP:
        if ((i + j) % 2 == 0)
        {
          chess_icon = gtk_image_new_from_file("./chess_icon/bBoW.png");
        }
        else
        {
          chess_icon = gtk_image_new_from_file("./chess_icon/bBoB.png");
        }
        break;
      case WKING:
        if ((i + j) % 2 == 0)
        {
          chess_icon = gtk_image_new_from_file("./chess_icon/wKoW.png");
        }
        else
        {
          chess_icon = gtk_image_new_from_file("./chess_icon/wKoB.png");
        }
        break;
      case WQUEEN:
        if ((i + j) % 2 == 0)
        {
          chess_icon = gtk_image_new_from_file("./chess_icon/wQoW.png");
        }
        else
        {
          chess_icon = gtk_image_new_from_file("./chess_icon/wQoB.png");
        }
        break;

      case WROOK:
        if ((i + j) % 2 == 0)
        {
          chess_icon = gtk_image_new_from_file("./chess_icon/wRoW.png");
        }
        else
        {
          chess_icon = gtk_image_new_from_file("./chess_icon/wRoB.png");
        }
        break;

      case WKNIGHT:
        if ((i + j) % 2 == 0)
        {
          chess_icon = gtk_image_new_from_file("./chess_icon/wNoW.png");
        }
        else
        {
          chess_icon = gtk_image_new_from_file("./chess_icon/wNoB.png");
        }

        break;

      case WPAWN:
        if ((i + j) % 2 == 0)
        {
          chess_icon = gtk_image_new_from_file("./chess_icon/wPoW.png");
        }
        else
        {
          chess_icon = gtk_image_new_from_file("./chess_icon/wPoB.png");
        }
        break;
      case WBISHOP:
        if ((i + j) % 2 == 0)
        {
          chess_icon = gtk_image_new_from_file("./chess_icon/wBoW.png");
        }
        else
        {
          chess_icon = gtk_image_new_from_file("./chess_icon/wBoB.png");
        }
        break;
      case a:
        chess_icon = gtk_image_new_from_file("./chess_icon/a.jpg");
        break;
      case b:
        chess_icon = gtk_image_new_from_file("./chess_icon/b.jpg");
        break;
      case c:
        chess_icon = gtk_image_new_from_file("./chess_icon/c.jpg");
        break;

      case d:
        chess_icon = gtk_image_new_from_file("./chess_icon/d.jpg");
        break;

      case e:
        chess_icon = gtk_image_new_from_file("./chess_icon/e.jpg");
        break;

      case f:
        chess_icon = gtk_image_new_from_file("./chess_icon/f.jpg");
        break;

      case g:
        chess_icon = gtk_image_new_from_file("./chess_icon/g.jpg");
        break;

      case h:
        chess_icon = gtk_image_new_from_file("./chess_icon/h.jpg");
        break;

      case one:
        chess_icon = gtk_image_new_from_file("./chess_icon/1.jpg");
        break;

      case two:
        chess_icon = gtk_image_new_from_file("./chess_icon/2.jpg");
        break;

      case three:
        chess_icon = gtk_image_new_from_file("./chess_icon/3.jpg");
        break;

      case four:
        chess_icon = gtk_image_new_from_file("./chess_icon/4.jpg");
        break;

      case five:
        chess_icon = gtk_image_new_from_file("./chess_icon/5.jpg");
        break;

      case six:
        chess_icon = gtk_image_new_from_file("./chess_icon/6.jpg");
        break;

      case seven:
        chess_icon = gtk_image_new_from_file("./chess_icon/7.jpg");
        break;

      case eight:
        chess_icon = gtk_image_new_from_file("./chess_icon/8.jpg");
        break;
      case ai:
        chess_icon = gtk_image_new_from_file("./chess_icon/AI'sTurn.jpg");
        break;

      default:
        break;
      }
      gtk_table_attach(GTK_TABLE(table), chess_icon, i, i + 1, j, j + 1, GTK_FILL, GTK_FILL, 0, 0);
    }
  }
}

void CoordToGrid(int c_x, int c_y, int *g_x, int *g_y)
{
  *g_x = (c_x - GBOARD_BORDER) / GSQUARE_SIZE;
  *g_y = ((c_y - GBOARD_BORDER) / GSQUARE_SIZE);
}

static gboolean
on_delete_event(GtkWidget *widget,
                GdkEvent *event,
                gpointer data)
{
  /* If you return FALSE in the "delete_event" signal handler,
   * GTK will emit the "destroy" signal. Returning TRUE means
   * you don't want the window to be destroyed.
   *
   * This is useful for popping up 'are you sure you want to quit?'
   * type dialogs.
   */
  char message[SLEN] = "shutdown";
  startClientConnection(15000, message);
  gtk_main_quit();
  return TRUE;
}

//Send message to chat window and server
static void sendMessage( GtkWidget *widget, gpointer   data )
{
  //save input text to array and add newline at the end
  char message[90];
  strcpy(message, gtk_entry_get_text(data));
  strcat(message, newline);
  //Reset the chat entry box
  gtk_entry_set_text(data,"");
  //save to const and print Me: to chat box
  const gchar *memessage = "Me: ";
  gtk_text_buffer_insert_at_cursor (chathistory, memessage, len);
  //insert newline if over certain amount of characters so can see whole message in window
  char *token = strtok(message, " ");
  char holder[80]; //can't be greater than 80 otherwise random block appears before
  while( token != NULL)
  {
    int curr = strlen(holder) - (strlen(holder)/30)*30;
    if (curr < 0)
       curr = 0;
    if((curr + strlen(token) + 1 ) < 30)
    {
      strcat(holder, token);
      strcat(holder, " ");      
    }
    else
    {
      strcat(holder, newline); 
      strcat(holder, token);
      strcat(holder, " ");
    }
    token = strtok(NULL, " ");
  }
  //save to const and print input message w/ newline to chat
  const gchar *constmessage = holder;
  gtk_text_buffer_insert_at_cursor (chathistory, constmessage, len); 
  //auto scroll to bottom if needed
  gtk_text_view_scroll_to_mark(GTK_TEXT_VIEW(chatbox), gtk_text_buffer_get_insert(chathistory), 0.0, TRUE, 0.5, 0.5);
  gtk_entry_set_text(data,"");
  //save message text into string with message: in front and send to server TO BE CODED
  char outmessage[100] = "message: ";
  strcat(outmessage, constmessage);
  g_print("Outmessage is:%s\n",outmessage); 
//send outmessage -> server TO BE CODED


}

gint area_click(GtkWidget *widget,
                GdkEvent *event,
                Board *thisGameBoard)
{
  static int i = -1;
  static int oldX, oldY;
  int x1, y1;
  //char arary words of size max_msglen which is defined in the header file length defined as 100
  char words[MAX_MSGLEN];
  //initialize int variables for the coordinantes
  int coord_x, coord_y, grid_x, grid_y;
  //create struct pointer BOARD, SQUARE
  struct Game *chess_board;
  struct SQUARE *chess_piece;
  struct SQUARE *piece_dest;
  //A set of bit-flags to indicate the state of modifier keys and mouse buttons in various event types. Typical modifier keys are Shift, Control, Meta, Super, Hyper, Alt, Compose, Apple, CapsLock or ShiftLock.
  GdkModifierType gState;
  //Obtains the current pointer position and modifier state. The position is given in coordinates relative to the upper left corner of window
  //x
  //
  //return location for X coordinate of pointer or NULL to not return the X coordinate
  //y
  //
  //return location for Y coordinate of pointer or NULL to not return the Y coordinate.
  //mask
  //
    //return location for modifier mask or NULL to not return the modifier mask.

  gdk_window_get_pointer(widget->window, &coord_x, &coord_y, &gState);
  //chnages coordinates to grid coordinates
  CoordToGrid(coord_x, coord_y, &grid_x, &grid_y);

  // Board Click Event Handling

  if (coord_x > 410 && coord_y > 410 && coord_x < 460 && coord_y < 460 && opp == 0) //Computer Player Use Only
  {
    if (((getGameTurn(thisGameBoard) != thisGameBoard->player1->playerColor && set == 0) || (getGameTurn(thisGameBoard) == thisGameBoard->player2->playerColor && set == 1)))
    {
      int nX, nY, nOX, nOY;
      char move[256];
      strcpy(move, startOppConnection(15000));
      sscanf(move, "(%d, %d) -> (%d, %d)", &nOX, &nOY, &nX, &nY);
      g_print("\n(%d, %d) -> (%d, %d)", nOX, 7-nOY, nX, 7-nY);
      MoveThePiece(nX, 7-nY, nOX, 7-nOY, thisGameBoard);
    }
  }
  else if (coord_x > 410 && coord_y > 410 && coord_x < 460 && coord_y < 460 && opp == 1) //Computer Player Use Only
  {
    MoveListNode *oppMove;
    if (cpuDiff == 3)
      oppMove = AIHardMove(thisGameBoard->player2, thisGameBoard);
    else if (cpuDiff == 2)
      oppMove = AImediummove(thisGameBoard->player2, thisGameBoard);
    else if (cpuDiff == 1)
      oppMove = AIeasymove(thisGameBoard->player2, thisGameBoard);

    assert(oppMove);

    int nOldX = getSquareXPos(oppMove->startSquare);

    int nOldY = getSquareYPos(oppMove->startSquare);

    int g_x = getSquareXPos(oppMove->endSquare);

    int g_y = getSquareYPos(oppMove->endSquare);

    /*ChessPiece *selectedPiece = thisGameBoard->chessBoard[nOldX][nOldY]->thisSquaresPiece;
    if ((getGameTurn(thisGameBoard) == selectedPiece->color))
    {
      char message[SLEN] = "\nwaiting for opp\n";
      startClientConnection(15000, message);
    }
    else{*/
      MoveThePiece(g_x, 7 - g_y, nOldX, 7 - nOldY, thisGameBoard);
  //  }
    deleteMoveList(oppMove->list);
  }
  else if (coord_x < 10 || coord_x > 410 || coord_y < 10 || coord_y > 410) // Clicked Outside of the Board
  {
    //User has clicked outside the board squares
  }
  else if (i == 2) // Select Piece
  {
    //char message[SLEN] = "move made";
    //startClientConnection(15000, message);

    //ChessPiece *selectedPiece = thisGameBoard->chessBoard[oldX][7-oldY]->thisSquaresPiece;
    if (((getGameTurn(thisGameBoard) != thisGameBoard->player1->playerColor && set == 0) || (getGameTurn(thisGameBoard) == thisGameBoard->player2->playerColor && set == 1)))
    {
      /*int nX, nY, nOX, nOY;
      char move[256];
      strcpy(move, startOppConnection(15000));
      sscanf(move, "(%d, %d) -> (%d, %d)", &nOX, &nOY, &nX, &nY);
      g_print("\n(%d, %d) -> (%d, %d)", nOX, 7-nOY, nX, 7-nY);
      MoveThePiece(nX, 7-nY, nOX, 7-nOY, thisGameBoard);*/
    }
    else{
      MoveThePiece(grid_x, grid_y, oldX, oldY, thisGameBoard);
      //char message[SLEN] = "\nwaiting for opp\n";
      //startClientConnection(15000, message);
    }

    //MoveThePiece(grid_x, grid_y, oldX, oldY, thisGameBoard);
    i = -1;
  }

  else if (Game[grid_x][grid_y] != SBLACK && Game[grid_x][grid_y] != SWHITE)
  {
    i = 2;
    oldX = grid_x;
    oldY = grid_y;
    return TRUE;
  }

  else
  {
    i = -1;
  }

  gtk_container_remove(GTK_CONTAINER(window), fixed);
  table = gtk_table_new(9, 9, TRUE);
  gtk_widget_set_size_request(table, GBOARD_WIDTH, GBOARD_HEIGHT);
  DrawBoard();

  /*set fixed*/

  fixed = gtk_fixed_new();
  gtk_fixed_put(GTK_FIXED(fixed), table, 0, 0);
  gtk_container_add(GTK_CONTAINER(window), fixed);
  gtk_widget_show_all(window);

  return TRUE;
}

int main(int argc,
         char *argv[])
{
  char str[GMAX_MSGLEN];

  gtk_init(&argc, &argv);
  //resets board to default mode

  state = fopen("state.txt", "r");
  fscanf(state, "opp%dset%ddiff%d", &opp, &set, &cpuDiff);
  fclose(state);
  current.opponent = opp;
  current.set_color = set;

  Color player1Color, player2Color;
  PlayerType player2Type;

  if (set == 0)
  {
    player1Color = WHITE;
    player2Color = BLACK;
  }
  else
  {
    player1Color = BLACK;
    player2Color = WHITE;
  }

  if (opp == 0)
  {
    player2Type = HUMAN;
  }
  else
  {
    player2Type = COMPUTER;
  }

  Player *player1 = createPlayer(WHITE, HUMAN);
  Player *player2 = createPlayer(BLACK, player2Type);

  Board *thisGameBoard = createGameBoard(player1Color);
  populateGameBoard(thisGameBoard, set);
  fillPlayerPieces(player1, thisGameBoard);
  fillPlayerPieces(player2, thisGameBoard);
  thisGameBoard->player1 = player1;
  thisGameBoard->player2 = player2;

  /*create a new window */
  //simply new window
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  hisWin = gtk_window_new(GTK_WINDOW_POPUP);
  chatwin = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  //request for window to be size of windowWidth and windowHeight defined in the header file
  gtk_widget_set_size_request(window, GWINDOW_WIDTH, GWINDOW_HEIGHT);
  gtk_widget_set_size_request(chatwin, GWINDOW_WIDTH / 2, GWINDOW_HEIGHT / 2);
  //set boarder width by window border defined in the header file
  gtk_container_set_border_width(GTK_CONTAINER(window), GWINDOW_BORDER);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_widget_set_size_request(hisWin, GWINDOW_WIDTH / 2, GWINDOW_HEIGHT / 2);
  gtk_container_set_border_width (GTK_CONTAINER (chatwin), 10);
  //set boarder width by window border defined in the header file
  gtk_container_set_border_width(GTK_CONTAINER(hisWin), GWINDOW_BORDER);
  gtk_window_set_position(GTK_WINDOW(hisWin), GTK_WIN_POS_CENTER);
  gtk_window_move(GTK_WINDOW(hisWin), 350, 400);
  gtk_window_set_transient_for(GTK_WINDOW(hisWin), GTK_WINDOW(window));
  gtk_window_set_title(GTK_WINDOW(window), "Chess Kings");
  gtk_window_set_title(GTK_WINDOW(hisWin), "Move History\n");
  gtk_window_set_title(GTK_WINDOW(chatwin), "Chat\n");
  gtk_window_move(GTK_WINDOW(chatwin), 1345, 400);

  // make window size fixed
  gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

  /*register event handlers*/
  //when the exit icon is pressed
  g_signal_connect(window, "delete_event", G_CALLBACK(on_delete_event), NULL);

  //set events for button press
  //Sets the event mask (see GdkEventMask) for a widget
  //The event mask determines which events a widget will receive
  gtk_widget_set_events(window, GDK_BUTTON_PRESS_MASK);
  //when a button is pressed call area_click
  //Signal will be emitted when a button (typically from a mouse) is pressed
  g_signal_connect(window, "button_press_event", G_CALLBACK(area_click), thisGameBoard);

  /*create a table and draw the board*/
  table = gtk_table_new(8, 10, TRUE);
  gtk_widget_set_size_request(table, GBOARD_WIDTH, GBOARD_HEIGHT);
  InitBoard(player2, thisGameBoard);
  DrawBoard();
  chatTable = gtk_table_new(10,4,TRUE);
  gtk_container_add (GTK_CONTAINER (chatwin), chatTable);

  fixed = gtk_fixed_new();
  gtk_fixed_put(GTK_FIXED(fixed), table, 0, 0);
  gtk_container_add(GTK_CONTAINER(window), fixed);

  moveHistory = gtk_text_view_new();
  scrollView = gtk_scrolled_window_new(NULL, NULL);
  history = gtk_text_view_get_buffer(GTK_TEXT_VIEW(moveHistory));
  gtk_text_buffer_get_iter_at_offset(history, &iter, 0);
  gtk_text_buffer_insert(history, &iter, "History of Moves:\n", -1);
  gtk_text_view_set_editable(GTK_TEXT_VIEW(moveHistory), FALSE);
  gtk_container_add(GTK_CONTAINER(scrollView), moveHistory);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollView), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
  gtk_container_add(GTK_CONTAINER(hisWin), scrollView);

  //create and place all widgets for chat gui in chat window
  chatscrollView = gtk_scrolled_window_new(NULL, NULL);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(chatscrollView), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
  gtk_table_attach_defaults (GTK_TABLE (chatTable), chatscrollView, 0, 4, 0, 9);


  chatbox = gtk_text_view_new();
  gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW(chatbox), FALSE);
  gtk_text_view_set_editable(GTK_TEXT_VIEW(chatbox), FALSE);
  chathistory = gtk_text_view_get_buffer(GTK_TEXT_VIEW(chatbox));
  gtk_container_add(GTK_CONTAINER(chatscrollView), chatbox);

	
  chatentry = gtk_entry_new();
  gtk_table_attach_defaults (GTK_TABLE (chatTable), chatentry, 0, 3, 9, 10);

  sendbutton = gtk_button_new_with_label ("Send");
  gtk_table_attach_defaults (GTK_TABLE (chatTable), sendbutton, 3,4, 9, 10);

  //signal connects for chat gui window & widgets
  g_signal_connect (chatwin, "delete-event", G_CALLBACK (on_delete_event), NULL);
  g_signal_connect (sendbutton, "clicked", G_CALLBACK (sendMessage), chatentry);
  g_signal_connect (chatentry, "activate", G_CALLBACK (sendMessage), chatentry); 

  promoted = malloc(sizeof(int));
  assert(promoted);

  mLog = fopen("GameLogs/GameLog.txt", "w");

//char inmessage = MESSAGEFROMSERVER;
  char inmessage[100] = "message: Hey good luck man";
//g_print("BEFORE trim: %s\n", inmessage);
  char *trimmed = strtok(inmessage, " ");
//g_print("trimmed part: %s\n", trimmed);
  trimmed = strtok(NULL, "\0");
//g_print("leftover: %s\n", trimmed);
  strcat(trimmed, newline);
  const gchar *OPmessage = "Opponent: ";
  gtk_text_buffer_insert_at_cursor (chathistory, OPmessage, len);
  const gchar *constOPmessage = trimmed;
  gtk_text_buffer_insert_at_cursor (chathistory, constOPmessage, len);

  /*show the window*/
  gtk_widget_show_all(window);
  gtk_widget_show_all(hisWin);
  gtk_widget_show_all(chatwin);

  gtk_main();

  deletePlayer(player1);
  deletePlayer(player2);
  free(promoted);
  deleteGameBoard(thisGameBoard);
  fclose(mLog);

  return 0;
}
