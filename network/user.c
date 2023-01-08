#include "user.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define CIPHER_KEY 23 //used for encryption/decryption

User *createUser(Player *player, int port, char username[], char password[])
{
  User *newUser = malloc(sizeof(User));

  newUser->player = player;
  newUser->playerPieces = *(player->playerPieces);
  newUser->port = port;

  for (int i = 0; i < 4; ++i)
  {
    newUser->contactList[i] = NULL;
  }

  strcpy(newUser->username, username);
  strcpy(newUser->password, password);

  return newUser;
}

void deleteUser(User *user)
{
  assert(user);
  user->player = NULL;
  user->playerPieces = NULL;
  user->port = -1000;

  strcpy(user->username, "deletedUser");
  strcpy(user->password, "deletedPasswrd");
  free(user);
}

int addContact(User *user, char username[], userList *list)
{
  int contactPosition = 0;
  for (int i = 0; i < 4; ++i)
  {
    if (user->contactList[i] != NULL)
    {
      contactPosition = i;
      break;
    }
  }

  userListNode *current = list->head, *next = NULL;

  while (current)
  {
    next = current->next;

    if (strcmp(current->thisUser->username, username) == 0) //check to see if the usernames are equal
    {
      user->contactList[contactPosition] = current->thisUser;
      return 1;
    }
    current = next;
  }

  return 0;
}

int deleteContact(User *user, char username[])
{
  for (int i = 0; i < 4; ++i) //iterate thru user contacts to check if contact exists
  {
    if (strcmp(user->contactList[i]->username, username) == 0)
    {
      user->contactList[i] = NULL;
      return 1;
    }
  }
  return 0;
}

void encryptPass(char unencryptedPassword[])
{
  for (int i = 0; strlen(unencryptedPassword) - 1; ++i)
  {
    unencryptedPassword[i] += CIPHER_KEY;
  }
}

void decryptPass(char encryptedPassword[])
{
  for (int i = 0; strlen(encryptedPassword) - 1; ++i)
  {
    encryptedPassword[i] -= CIPHER_KEY;
  }
}