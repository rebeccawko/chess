#include "chessServer.h"

void FatalError(const char *Program, const char *ErrorMsg)
{
    fputs(Program, stderr);
    fputs(": ", stderr);
    perror(ErrorMsg);
    fputs(Program, stderr);
    fputs(": Exiting!", stderr);
    exit(20);
} /* end of FatalError */
int startConnection(int portNum){

  int l, n;
  int ServSocketFD,	/* socket file descriptor for service */
  DataSocketFD;	/* socket file descriptor for data */
  socklen_t ClientLen;
  struct sockaddr_in
  ServerAddress,	/* server address (this host) */
  ClientAddress;	/* client address we connect with */
  char RecvBuf[256];	/* message buffer for receiving a message */
  char SendBuf[256];	/* message buffer for sending a response */
  char moveBuf[256];
  char move[256];
  int Bye = 0,
  Shutdown = 0;

  printf("%s: Starting...\n", PORTNAME);
  /*if (argc < 2)
  {   fprintf(stderr, "Usage: %s port\n", PORTNAME);
  exit(10);
}*/
  //#ifdef DEBUG
  printf("%s: Using port %d...\n", PORTNAME, portNum);
  //#endif
  if (portNum <= 2000)
  {   fprintf(stderr, "%s: invalid port number %d, should be greater 2000\n",
  PORTNAME, portNum);
      exit(10);
  }
  //#ifdef DEBUG
  printf("%s: Creating a socket to serve clients...\n", PORTNAME);
  //#endif
  ServSocketFD = socket(AF_INET, SOCK_STREAM, 0);
  if (ServSocketFD < 0)
  {   FatalError(PORTNAME, "service socket creation failed");
  }
  //#ifdef DEBUG
  printf("%s: Preparing the server address...\n", PORTNAME);
  //#endif
  memset(&ServerAddress, 0, sizeof(ServerAddress));
  ServerAddress.sin_family = AF_INET;
  ServerAddress.sin_port = htons(portNum);
  ServerAddress.sin_addr.s_addr = INADDR_ANY;
  //#ifdef DEBUG
  printf("%s: Assigning the server name to the socket...\n", PORTNAME);
  //#endif
  if (bind(ServSocketFD, (struct sockaddr*)&ServerAddress,
  sizeof(ServerAddress)) < 0)
  {   FatalError(PORTNAME, "binding the server to a socket failed");
  }
  printf("%s: Listening on port %d...\n", PORTNAME, portNum);
  if (listen(ServSocketFD, 5) < 0)	/* max 5 clients in backlog */
  {   FatalError(PORTNAME, "listening on socket failed");
  }
  strcpy(move,"hello");
  move[sizeof(move)-1] = 0;
  do{ Shutdown = 0;
  ClientLen = sizeof(ClientAddress);
  DataSocketFD = accept(ServSocketFD, (struct sockaddr*)&ClientAddress,
  &ClientLen);
  if (DataSocketFD < 0)
  {   FatalError(PORTNAME, "data socket creation (accept) failed");
  }
  printf("%s: Accepted connection from client.\n", PORTNAME);
  #ifdef DEBUG
  printf("%s: Client address:port = %u:%hu.\n", PORTNAME,
    ClientAddress.sin_addr.s_addr, ntohs(ClientAddress.sin_port));
  #endif
  do{ Bye = 0;
    strncpy(moveBuf, move, sizeof(moveBuf)-1);
    moveBuf[sizeof(moveBuf)-1] = 0;
    l = strlen(moveBuf);
    printf("%s: Sending greeting: %s.\n", PORTNAME, moveBuf);
    n = write(DataSocketFD, moveBuf, l);
    if (n < 0)
    {   FatalError(PORTNAME, "writing to data socket failed");
  }

    n = read(DataSocketFD, RecvBuf, sizeof(RecvBuf)-1);
    if (n < 0)
    {   FatalError(PORTNAME, "reading from data socket failed");
    }
    RecvBuf[n] = 0;
    printf("%s: Received message: %s\n", PORTNAME, RecvBuf);
    if (0 == strcmp(RecvBuf, "bye"))
    {   Bye = 1;
  #ifdef DEBUG
  printf("%s: Received 'bye' message from client.\n", PORTNAME);
  #endif
  strncpy(SendBuf, "server bye", sizeof(SendBuf)-1);
  SendBuf[sizeof(SendBuf)-1] = 0;
    }
    else if (0 == strcmp(RecvBuf, "shutdown"))
    {   Shutdown = 1;
  #ifdef DEBUG
  printf("%s: Received 'shutdown' message from client.\n", PORTNAME);
  #endif
  strncpy(SendBuf, "server shutdown", sizeof(SendBuf)-1);
  SendBuf[sizeof(SendBuf)-1] = 0;
    }
    else
    {
      strcpy(move,RecvBuf);
      move[sizeof(move)-1] = 0;
      printf("\n%s\n", move);
      strncpy(SendBuf, "server echo ", sizeof(SendBuf)-1);
  SendBuf[sizeof(SendBuf)-1] = 0;
  strncat(SendBuf, RecvBuf, sizeof(SendBuf)-1-strlen(SendBuf));
    }
    printf("\n%s\n", SendBuf);
    l = strlen(SendBuf);
    printf("%s: Sending response: %s.\n", PORTNAME, SendBuf);
    n = write(DataSocketFD, SendBuf, l);
    if (n < 0)
    {   FatalError(PORTNAME, "writing to data socket failed");
    }

    n = read(DataSocketFD, RecvBuf, sizeof(RecvBuf)-1);
    if (n < 0)
    {   FatalError(PORTNAME, "reading from data socket failed");
    }
    RecvBuf[n] = 0;
    printf("%s: Received message: %s\n", PORTNAME, RecvBuf);
    if (0 == strcmp(RecvBuf, "bye"))
    {   Bye = 1;
  #ifdef DEBUG
  printf("%s: Received 'bye' message from client.\n", PORTNAME);
  #endif
  strncpy(SendBuf, "server bye", sizeof(SendBuf)-1);
  SendBuf[sizeof(SendBuf)-1] = 0;
    }
    else if (0 == strcmp(RecvBuf, "shutdown"))
    {   Shutdown = 1;
  #ifdef DEBUG
  printf("%s: Received 'shutdown' message from client.\n", PORTNAME);
  #endif
  strncpy(SendBuf, "server shutdown", sizeof(SendBuf)-1);
  SendBuf[sizeof(SendBuf)-1] = 0;
    }
    else
    {   strncpy(SendBuf, "server echo ", sizeof(SendBuf)-1);
  SendBuf[sizeof(SendBuf)-1] = 0;
  strncat(SendBuf, RecvBuf, sizeof(SendBuf)-1-strlen(SendBuf));
    }
    printf("\n%s\n", SendBuf);
    l = strlen(SendBuf);
    printf("%s: Sending response: %s.\n", PORTNAME, SendBuf);
    n = write(DataSocketFD, SendBuf, l);
    if (n < 0)
    {   FatalError(PORTNAME, "writing to data socket failed");
    }

  } while(!Bye && !Shutdown);
  printf("%s: Received last message from client, closing data connection.\n", PORTNAME);
  close(DataSocketFD);

  } while(!Shutdown);

  printf("%s: Shutting down.\n", PORTNAME);
  close(ServSocketFD);

  return 0;

}
int main(){
  startConnection(15000);
  return 0;
}
