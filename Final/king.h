#ifndef __KING_H__
#define __KING_H__

#include"move.h"
#include"piece.h"
#include<string>
//#include"board.h"

class King: public Piece{
	public:
	King(std::string,Board*);
	bool checkingCastles;
	vector<Move> validCastles(string);		//returns a vector of valid castling moves
	private:
	vector<Move> getValidMoves(std::string, bool);	//returns a vector of all valid moves
};
#endif
