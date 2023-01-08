#ifndef __USER_H__
#define __USER_H__

#include "networkStructs.h"

User *createUser(Player *player, int port, char username[], char password[]);

void deleteUser(User *user);

void encryptPass(char unencryptedPassword[]);

int addContact(User *user, char username[], userList *list); //returns 1 if successful, 0 if the username doesn't exist

int deleteContact(User *user, char username[]); //returns 1 if successful, 0 if the username doesn't exist

#endif