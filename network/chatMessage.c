#include "chatMessage.h"
#include <stdlib.h>

chatMessage *createChatMessage(User *sender)
{
  chatMessage *newMessage = malloc(sizeof(chatMessage));
  newMessage->sender = sender;
  return newMessage;
}

char *getMessage(chatMessage *messageInstance)
{
  return messageInstance->message;
}

void setMessage(char *message, chatMessage *messageInstance)
{
  messageInstance->message = message;
}