#include "chessClient.h"

void FatalError(const char *Program, const char *ErrorMsg)
{
    fputs(Program, stderr);
    fputs(": ", stderr);
    perror(ErrorMsg);
    fputs(Program, stderr);
    fputs(": Exiting!", stderr);
    exit(20);
} /* end of FatalError */

char *startOppConnection(int portNum){
  int l, n;
  int SocketFD;	/* socket file descriptor */
  struct sockaddr_in
ServerAddress;	/* server address we connect with */
  struct hostent
*Server;	/* server host */
  char SendBuf[SLEN];	/* message buffer for sending a message */
  char RecvBuf[SLEN];	/* message buffer for receiving a response */
  char move[SLEN];

  printf("%s: Starting...\n", CLIENTNAME);
  /*if (argc < 3)
  {   fprintf(stderr, "Usage: %s hostname port\n", CLIENTNAME);
exit(10);
}*/
//#ifdef DEBUG
  printf("%s: Looking up host %s on the network...\n", CLIENTNAME, HOSTNAME);
//#endif
  Server = gethostbyname(HOSTNAME);
  if (Server == NULL)
  {   fprintf(stderr, "%s: no such host named '%s'\n", CLIENTNAME, HOSTNAME);
      exit(10);
  }
  //portNum = atoi(portNum);
//#ifdef DEBUG
  printf("%s: Using port %d...\n", CLIENTNAME, portNum);
//#endif
  if (portNum <= 2000)
  {   fprintf(stderr, "%s: invalid port number %d, should be greater 2000\n",
  CLIENTNAME, portNum);
      exit(10);
  }
//#ifdef DEBUG
  printf("%s: Creating a socket...\n", CLIENTNAME);
//#endif
  SocketFD = socket(AF_INET, SOCK_STREAM, 0);
  if (SocketFD < 0)
  {   FatalError(CLIENTNAME, "socket creation failed");
  }
//#ifdef DEBUG
  printf("%s: Preparing the server address...\n", CLIENTNAME);
//#endif
  memset(&ServerAddress, 0, sizeof(ServerAddress));
  ServerAddress.sin_family = AF_INET;
  ServerAddress.sin_port = htons(portNum);
  memcpy(&ServerAddress.sin_addr.s_addr,
  Server->h_addr_list[0], Server->h_length);
  printf("%s: Connecting to the server...\n", CLIENTNAME);
  if (connect(SocketFD, (struct sockaddr*)&ServerAddress,
  sizeof(ServerAddress)) < 0)
  {   FatalError(CLIENTNAME, "connecting to server failed");
  }

  do{
    /*printf("%s: enter a message to send to the server,\n"
  "         or 'bye' to quit this client,\n"
  "         or 'shutdown' to quit both server and client:\n"
  "message: ", CLIENTNAME);*/
//fgets(SendBuf, sizeof(SendBuf), Message);
    n = read(SocketFD, RecvBuf, sizeof(RecvBuf)-1);
    if (n < 0)
    {   FatalError(CLIENTNAME, "reading from socket failed");
    }
    RecvBuf[n] = 0;
    strcpy(move, RecvBuf);
    printf("%s: Received response: %s\n", CLIENTNAME, RecvBuf);
    n = write(SocketFD, "bye", l);

    n = read(SocketFD, RecvBuf, sizeof(RecvBuf)-1);
    if (n < 0)
    {   FatalError(CLIENTNAME, "reading from socket failed");
    }
    RecvBuf[n] = 0;
    printf("%s: Received response 2: %s\n", CLIENTNAME, RecvBuf);
}
  while(  (0 != strcmp("server bye", RecvBuf))
    &&(0 != strcmp("server shutdown", RecvBuf)));
  printf("%s: Exiting...\n", CLIENTNAME);
  close(SocketFD);
  return move;
}

int startClientConnection(int portNum, char Message[SLEN]){
  int l, n;
  int SocketFD;	/* socket file descriptor */
  struct sockaddr_in
ServerAddress;	/* server address we connect with */
  struct hostent
*Server;	/* server host */
  char SendBuf[SLEN];	/* message buffer for sending a message */
  char RecvBuf[SLEN];	/* message buffer for receiving a response */

  printf("%s: Starting...\n", CLIENTNAME);
  /*if (argc < 3)
  {   fprintf(stderr, "Usage: %s hostname port\n", CLIENTNAME);
exit(10);
}*/
//#ifdef DEBUG
  printf("%s: Looking up host %s on the network...\n", CLIENTNAME, HOSTNAME);
//#endif
  Server = gethostbyname(HOSTNAME);
  if (Server == NULL)
  {   fprintf(stderr, "%s: no such host named '%s'\n", CLIENTNAME, HOSTNAME);
      exit(10);
  }
  //portNum = atoi(portNum);
//#ifdef DEBUG
  printf("%s: Using port %d...\n", CLIENTNAME, portNum);
//#endif
  if (portNum <= 2000)
  {   fprintf(stderr, "%s: invalid port number %d, should be greater 2000\n",
  CLIENTNAME, portNum);
      exit(10);
  }
//#ifdef DEBUG
  printf("%s: Creating a socket...\n", CLIENTNAME);
//#endif
  SocketFD = socket(AF_INET, SOCK_STREAM, 0);
  if (SocketFD < 0)
  {   FatalError(CLIENTNAME, "socket creation failed");
  }
//#ifdef DEBUG
  printf("%s: Preparing the server address...\n", CLIENTNAME);
//#endif
  memset(&ServerAddress, 0, sizeof(ServerAddress));
  ServerAddress.sin_family = AF_INET;
  ServerAddress.sin_port = htons(portNum);
  memcpy(&ServerAddress.sin_addr.s_addr,
  Server->h_addr_list[0], Server->h_length);
  printf("%s: Connecting to the server...\n", CLIENTNAME);
  if (connect(SocketFD, (struct sockaddr*)&ServerAddress,
  sizeof(ServerAddress)) < 0)
  {   FatalError(CLIENTNAME, "connecting to server failed");
  }

  do{
    /*printf("%s: enter a message to send to the server,\n"
  "         or 'bye' to quit this client,\n"
  "         or 'shutdown' to quit both server and client:\n"
  "message: ", CLIENTNAME);*/
//fgets(SendBuf, sizeof(SendBuf), Message);
n = read(SocketFD, RecvBuf, sizeof(RecvBuf)-1);
if (n < 0)
{   FatalError(CLIENTNAME, "reading from socket failed");
}
RecvBuf[n] = 0;
printf("%s: Received greeting: %s\n", CLIENTNAME, RecvBuf);

strcpy(SendBuf, Message);
l = strlen(SendBuf);
if (SendBuf[l-1] == '\n')
{   SendBuf[--l] = 0;
}
if (l)
{   printf("%s: Sending message '%s'...\n", CLIENTNAME, SendBuf);
    n = write(SocketFD, SendBuf, l);
    if (n < 0)
    {   FatalError(CLIENTNAME, "writing to socket failed");
    }
//#ifdef DEBUG
    printf("%s: Waiting for response...\n", CLIENTNAME);
//#endif
    n = read(SocketFD, RecvBuf, sizeof(RecvBuf)-1);
    if (n < 0)
    {   FatalError(CLIENTNAME, "reading from socket failed");
    }
    RecvBuf[n] = 0;
    printf("%s: Received response: %s\n", CLIENTNAME, RecvBuf);

    strcpy(SendBuf, Message);
    l = strlen(SendBuf);
    if (SendBuf[l-1] == '\n')
    {   SendBuf[--l] = 0;
    }
    n = write(SocketFD, "bye", l);

    printf("%s: Waiting for response 2...\n", CLIENTNAME);
//#endif
    n = read(SocketFD, RecvBuf, sizeof(RecvBuf)-1);
    if (n < 0)
    {   FatalError(CLIENTNAME, "reading from socket failed");
    }
    RecvBuf[n] = 0;
    printf("%s: Received response 2: %s\n", CLIENTNAME, RecvBuf);
}
  } while(  (0 != strcmp("server bye", RecvBuf))
    &&(0 != strcmp("server shutdown", RecvBuf)));
  printf("%s: Exiting...\n", CLIENTNAME);
  close(SocketFD);
  return 0;
}

/*int main() {
  char message[SLEN] = "shutdown";
  startClientConnection(15000, message);

  return 0;
}*/
