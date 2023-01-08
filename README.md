# Kings of Chess (Team15 Spring 2020)

Kings of Chess is a chess application that allows you to play against another human or against a computer opponent.

## Installation

Download the Chat_Alpha_src.tar.gz file and use [tar](https://www.gnu.org/software/tar/) to extract the Kings of Chess files.

```bashk
$ gtar -xvzf Chat_Alpha_src.tar.gz
```

## Usage

### Server

To start the Chess Server, run the makefile in the bin directory and run the Server

```bash
~/Team15 $ cd bin
~/Team15/bin $ make server
 ```

NOTE: Once the server has been shut down, it cannot be restarted for 60 seconds

### Chess App

After extracting the files, run the makefile once you're in the directory created by extracting the files to compile and run the program

```bash
~/Team15 $ cd bin
~/Team15/bin $ rm state.txt
~/Team15/bin $ make run
```

In order to receive the opponent's move, press white square in the bottom rightmost corner of the window when it is the opponents move.

Once you run these commands, you will be brought to the startup screen for Kings of Chess! To play again once your game ends, type

```bash
~/Team15/bin $ make run
```

### Testing

In order to test the app without having to play against another opponent, use the dummy client in the bin/clientTest directory

```bash
~/Team15 $ cd bin/clientTest
~/Team15/bin $ make test
 ```

 Input the move you want the "opponent" to make in the format (x, y) -> (x, y).
 NOTE: The (x, y) range is (0, 0) to (7, 7) with (0, 0) being the bottom leftmost square and (7, 7) being the top rightmost square.

## Gameplay

When you first enter the game you will encounter the main menu screen where you have the option to start a new game or go to a help screen. To go start playing, click "New Game" then click on whether you want to play vs a human or computer, then click the color you want to be. After selecting your opponent and color, click "Start Game" and your game will be started. From here you can play Kings of Chess in all its glory!

## Uninstallation

To uninstall ChessKings, go to the root directory
```bash
~/ $ cd ..
```
Delete all the files
```bash
~/ $ rm -rf *

```
# Copyright
Copyright
© 2020 Aviraj Mukherjee, Martin Alexander Gomez, Henry Thy Bendiksen, Sarthak Sharma, Rebecca Ko

This software is free and is licensed under GNU General Public License, version 3.0. You are welcome to redistribute it under certain conditions. More information can be found on <https://www.gnu.org/licenses/gpl-3.0.html>.
