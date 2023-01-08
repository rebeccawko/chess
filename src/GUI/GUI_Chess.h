/***********************************************************
*
*A simple GTK example
*simple.h: show a 2x2 board and move the king by clicking
*author: Weiwei Chen
*initial version: 01/22/13 EECS22L Winter 2013
*
***********************************************************/

#ifndef _SIMPLE_H
#define _SIMPLE_H


#define GMAX_MSGLEN  100
#define GSQUARE_SIZE 50
#define GWINDOW_BORDER 10
#define GBOARD_BORDER 10
#define GBOARD_WIDTH  (9*GSQUARE_SIZE)
#define GBOARD_HEIGHT (9*GSQUARE_SIZE)
#define GWINDOW_WIDTH  (GBOARD_WIDTH + 2*GBOARD_BORDER)
#define GWINDOW_HEIGHT (GBOARD_HEIGHT + 2*GBOARD_BORDER)
#define WIN_MESSAGE "Congrats! You Win!\n"
#define LOSS_MESSAGE "Sorry. You Lost.\n"

enum GRID
{
	SBLACK = 0,
	SWHITE = 1,
	BKING=2,
	BQUEEN=3,
	BROOK=4,
	BBISHOP=5,
	BKNIGHT=6,
	BPAWN=7,
	WKING=8,
	WQUEEN=9,
	WROOK=10,
	WBISHOP=11,
	WKNIGHT=12,
	WPAWN=13,
	a,b,c,d,e,f,g,h,one,two,three,four,five,six,seven,eight,ai

};


#endif
