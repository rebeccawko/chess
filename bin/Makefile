# This is the makefile for the chess app

GTKINC	= `PKG_CONFIG_PATH=/usr/share/pkgconfig pkg-config --cflags gtk+-2.0`
GTKLIBS	= `PKG_CONFIG_PATH=/usr/share/pkgconfig pkg-config --libs gtk+-2.0`

INC	= $(GTKINC)
LIBS	= $(GTKLIBS)
GUI = ../src/GUI/
BIN =
SRC = ../src/
NTWRK = ../network/

OPTS	= -g

PROJECT	= ChessKings GUI_Chess

CFLAGS = -ansi -std=c99 -Wall -c	-g			#Compile flags
DEBUG = $(OPTS) -DDEBUG

all: main

proj: $(PROJECT)

#START SERVER/CLIENT TARGETS
host: $(NTWRK)chessServer.c $(NTWRK)chessServer.h
	gcc $(CFLAGS) $(NTWRK)chessServer.c -o $(BIN)chessServer.o

upload: host
	gcc -g $(BIN)chessServer.o -o $(BIN)ChessServer

client: $(NTWRK)chessClient.c $(NTWRK)chessClient.h
	gcc $(CFLAGS) $(NTWRK)chessClient.c -o $(BIN)chessClient.o

connect: client
	gcc -g $(BIN)chessClient.o -o $(BIN)ChessClient

server:
	make host
	make upload
	./ChessServer

#END SERVER/CLIENT TARGETS

#START LOGIC TARGETS
main: square moveList pieces player board
	gcc -g $(SRC)main.c $(BIN)square.o $(BIN)moveList.o $(BIN)pieces.o $(BIN)player.o $(BIN)board.o -o $(BIN)ChessGame


square: $(SRC)square.c $(SRC)square.h
	gcc $(CFLAGS) $(SRC)square.c -o $(BIN)square.o


moveList: $(SRC)moveList.c $(SRC)moveList.h
	gcc $(CFLAGS) $(SRC)moveList.c -o $(BIN)moveList.o


pieces: $(SRC)pieces.c $(SRC)pieces.h
	gcc $(CFLAGS) $(SRC)pieces.c -o $(BIN)pieces.o


player: $(SRC)player.c $(SRC)player.h
	gcc $(CFLAGS) $(SRC)player.c -o $(BIN)player.o


board: $(SRC)board.c $(SRC)board.h
	gcc $(CFLAGS) $(SRC)board.c -o $(BIN)board.o
#END LOGIC TARGETS

#START GUI TARGETS
main-menu.o: $(GUI)main-menu.c $(GUI)main-menu.h
	gcc -c $(GUI)main-menu.c $(INC) $(OPTS) -o $(BIN)main-menu.o

ChessKings: main-menu.o
	gcc $(BIN)main-menu.o $(LIBS) $(OPTS) -o $(BIN)ChessKings

GUI_Chess.o: $(GUI)GUI_Chess.c $(GUI)GUI_Chess.h
		gcc -c $(GUI)GUI_Chess.c $(INC) $(OPTS) -o $(BIN)GUI_Chess.o

GUI_Chess: GUI_Chess.o $(BIN)square.o $(BIN)pieces.o $(BIN)board.o $(BIN)player.o $(BIN)moveList.o $(NTWRK)chessClient.o
		gcc $(BIN)GUI_Chess.o $(BIN)square.o $(BIN)pieces.o $(BIN)board.o $(BIN)player.o $(BIN)moveList.o $(NTWRK)chessClient.o $(LIBS) $(OPTS) -o $(BIN)GUI_Chess
#END START GUI TARGETS

#START NETWORK TARGETS
chatMessage: $(NTWRK)chatMessage.c $(NTWRK)chatMessage.h
	gcc $(CFLAGS) $(NTWRK)chatMessage.c -o $(BIN) chatMessage.o

userList: $(NTWRK)userList.c $(NTWRK)userList.h
	gcc $(CFLAGS) $(NTWRK)userList.c -o $(BIN) userList.o

gameInstance: $(NTWRK)gameInstance.c $(NTWRK)gameInstance.h
	gcc $(CFLAGS) $(NTWRK)gameInstance.c -o $(BIN)gameInstance.o

user: $(NTWRK)user.c $(NTWRK)user.h
	gcc $(CFLAGS) $(NTWRK)user.c -o $(BIN)user.o

#END NETWORK TARGETS



#START COMPILATION UTIL TARGET
clean:
	rm -f $(BIN)*.o $(BIN)ChessGame $(BIN)GUI_Chess $(BIN)ChessKings $(BIN)ChessClient $(BIN)ChessServer state.txt bin/GameLogs/GameLog.txt

game:
	make clean
	make proj
	$(BIN)./GUI_Chess

run:
	make clean
	make main
	make proj
	$(BIN)./ChessKings
#END COMPILATION UTIL TARGET

#TAR PROJECT COMPRESSION TARGET, this gives Error 1 but tar.gz file is created successfully
tar:
	tar --exclude-vcs --exclude=./USER_PACKAGE --exclude=./releases -czvf ../releases/Chat_Alpha_src.tar.gz ../../Team15 --warning=no-file-changed

userpkg:
	tar --exclude-vcs -czvf ../releases/Chat_Alpha.tar.gz ../USER_PACKAGE --warning=no-file-changed
