#ifndef __BOARD_H__
#define __BOARD_H__

#include<iostream>
#include"textdisplay.h"
//#include"window.h"
#include"move.h"
#include"square.h"
#include"piece.h"
#include<vector>

class Board {
	TextDisplay* td;
	public:
	void doMove(Move);
	void undoMove(Move);
	bool validLocation(string);
	Square** theBoard;
	void setup();
	void setAttacks();			//sets up all of the pieces' canAttack vector with moves they can currently do that capture a piece
	void tickPawn();			//disables a pawns ability to en passant
	Board(TextDisplay*);
	string gameStatus(string);		//checks if the given player is in check, checkmate, stalemate or no special circumstance
	~Board();
};

#endif
