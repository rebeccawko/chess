#ifndef __GAMEINSTANCE_H__
#define __GAMEINSTANCE_H__

#include "networkStructs.h"

gameInstance *createGameInstance(void);

void deleteGameInstance(gameInstance *game);

void setPlayer1(gameInstance *game, User *user);

void setPlayer2(gameInstance *game, User *user);

#endif