#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>

#define SLEN 256
#define HOSTNAME "bondi.eecs.uci.edu"
#define CLIENTNAME "Chess Kings"

void FatalError(const char *Program, const char *ErrorMsg);

int startClientConnection(int portNum, char Message[SLEN]);

char *startOppConnection(int portNum);

int closeClientConnection(int portNum);

int startClient();
