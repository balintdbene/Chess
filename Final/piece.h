#ifndef __PIECE_H__
#define __PIECE_H__

//#include"move.h"
#include<string>
#include<vector>
//#include<window.h>
//#include"board.h"

using std::string;
using std::vector;
class Board;

class Xwindow;

class Piece{
	public:
	int left;		//int values for en passant
	int right;
	bool hasMoved;		//keeps track of whether the piece has moved or not
	int value;
	string team;
	char type;
	bool underAttack;	//if the piece is under attack
	Board* chessboard;
	Move setMove(string,string,Board*);
	std::vector<Move> canAttack;
	bool validMove(string,string, bool);	//a valid move, may be asked to check independantly of any cases of check
	bool hypothesis(int, int, int, int);	//checks if a move puts the king in check
	virtual vector<Move> getValidMoves(string,bool)=0;	//each piece has their own implementation for a valid move
};

#endif
