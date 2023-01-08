#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>

#define SLEN 256
#define PORTNAME "Chess Kings"

//char move[SLEN];

void FatalError(const char *Program, const char *ErrorMsg);

int startConnection(int portNum);

int closeConnection(int portNum);

int startServer();
