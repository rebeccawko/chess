#ifndef __CHATMESSAGE_H___
#define __CHATMESSAGE_H__

#include "networkStructs.h"

chatMessage *createChatMessage(User *user);

char *getMessage(chatMessage *messageInstance);

void setMessage(char *message, chatMessage *messageInstance);

#endif