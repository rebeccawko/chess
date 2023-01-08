#include "gameInstance.h"
#include <assert.h>
#include <stdlib.h>

gameInstance *createGameInstance(void)
{
  gameInstance *newGame = malloc(sizeof(gameInstance));

  return newGame;
}

void setPlayer1(gameInstance *game, User *user) //assume player 1 is always white and initilize the gameboard to his position
{
  assert(game);
  assert(user);

  game->player1 = user;
}

void setPlayer2(gameInstance *game, User *user)
{
  assert(game);
  assert(user);

  game->player2 = user;
}