#ifndef __USERLIST_H__
#define __USERLIST_H__

#include "networkStructs.h"

userList *createUserList(void);

void deleteUserList(userList *list);

userListNode *createUserNode(User *user, userList *list);

void deleteUserNode(userListNode *node);

void appendUserNode(User *user, userList *list);

void removeUserNode(User *user, userList *list); //remove a user node from the list

#endif