#ifndef __PLAYER_H__
#define __PLAYER_H__

#include"move.h"
#include"board.h"
#include<vector>

using std::vector;

class Player{
	public:
	string team;
	Board* chessboard;	//a pointer to the chessboard so that the player can "see" whats going on
	virtual Move getMove() = 0;	//every player has their own way of choosing a move to do
};

#endif
