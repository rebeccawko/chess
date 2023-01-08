#include "userList.h"
#include <stdlib.h>

userList *createUserList(void)
{
  userList *newList = malloc(sizeof(userList));
  newList->length = 0;

  return newList;
}

userListNode *createUserNode(User *user, userList *list)
{
  userListNode *newNode = malloc(sizeof(userListNode));

  newNode->thisUser = user;
  newNode->list = list;
  newNode->next = NULL;

  return newNode;
}

void deleteUserNode(userListNode *node)
{
  free(node);
}

void appendUserNode(User *user, userList *list)
{
  userListNode *newNode = createUserNode(user, list);

  if (!(list->head))
  {
    list->head = newNode;
  }
  else
  {
    list->tail->next = newNode;
  }

  list->tail = newNode;
  list->length++;
}

void removeUserNode(User *user, userList *list) //decide whether removing the node will delete the user as well
{
  userListNode *current = list->head, *prev = NULL;

  if (list->head->thisUser == user)
  {
    deleteUserNode(list->head);
    list->length--;
    return;
  }

  while (current != NULL && current->thisUser != user)
  {
    prev = current;
    current = current->next;
  }

  // if the node was not present in the list
  if (!current)
  {
    return;
  }

  prev->next = current->next;
  list->length--;
  deleteUserNode(current);
}