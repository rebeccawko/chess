# Kings of Chess (Team15 Spring 2020)

Kings of Chess is a chess application that allows you to play against another human or against a computer opponent.

## Installation

Download the Chess_Kings.tar.gz file and use [tar](https://www.gnu.org/software/tar/) to extract the Kings of Chess files.

```bashk
$ gtar -xvzf Chess_Kings.tar.gz
```

## Usage

### Server

To start the Chess Server, run the makefile in the bin directory and run the Server

```bash
~/USER_PACKAGE $ cd bin
~/USER_PACKAGE/bin $ ./ChessServer
 ```

 NOTE: Once the server has been shut down, it cannot be restarted for 60 seconds

### Chess App

After extracting the files, clear the state of the program and run the application

```bash
~/USER_PACKAGE $ cd bin
~/USER_PACKAGE/bin $ rm state.txt bin/GameLogs/GameLog.txt
~/USER_PACKAGE/bin $ ./ChessKings
```
Once you run these commands, you will be brought to the startup screen for Kings of Chess! To play again once your game ends,  start the server once again and type

```bash
~/USER_PACKAGE/bin $ rm state.txt
~/USER_PACKAGE/bin $ ./ChessKings
```

## Gameplay

When you first enter the game you will encounter the main menu screen where you have the option to start a new game or go to a help screen. To go start playing, click "New Game" then click on whether you want to play vs a human or computer, then click the color you want to be. After selecting your opponent and color, click "Start Game" and your game will be started. From here you can play Kings of Chess in all its glory!

## Uninstallation

To uninstall ChessKings, go to the root directory, if you are not already there
```bash
~/ $ cd ..
```
Delete the folder containing the rest of the game files
```bash
~/ $ rm -rf  *

```
# Copyright
Copyright
© 2020 Aviraj Mukherjee, Martin Alexander Gomez, Henry Thy Bendiksen, Sarthak Sharma, Rebecca Ko

This software is free and is licensed under GNU General Public License, version 3.0. You are welcome to redistribute it under certain conditions. More information can be found on <https://www.gnu.org/licenses/gpl-3.0.html>.
