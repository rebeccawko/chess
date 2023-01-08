#ifndef __NETWORKSTRUCTS_H__
#define __NETWORKSTRUCTS_H__

#define MSGLEN 256
#define NAMELEN 50

#include "../src/chessStructs.h"

typedef struct userStruct User;
typedef struct chatMessageStruct chatMessage;
typedef struct userListStruct userList;
typedef struct userListNodeStruct userListNode;
typedef struct gameInstanceStruct gameInstance;

struct chatMessageStruct //each message that's sent
{
  char *message;
  User *sender;
  User *reciever;
};

struct userStruct //each user that logs into the server
{
  Player *player; //what player this user is (once game is initilized)
  ChessPiece *playerPieces;
  int port;
  Board *gameBoardState; //state of the client side gameboard
  User *contactList[4];  //list of user's contacts (friends)
  char username[NAMELEN];
  char password[NAMELEN];
};

struct gameInstanceStruct
{
  Board *chessBoard; //state of the board on the server
  User *player1;
  User *player2;
};

struct userListStruct //used by server to keep track of all the users
{
  userListNode *head;
  userListNode *tail;

  int length;
};

struct userListNodeStruct
{
  User *thisUser;
  userList *list;

  userListNode *next;
};

#endif
