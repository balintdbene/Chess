#ifndef __KNIGHT_H__
#define __KNIGHT_H__

//#include"move.h"
#include"piece.h"
#include<string>
//#include"board.h"

class Knight: public Piece{
	public:
	Knight(std::string,Board*);
	private:
	vector<Move> getValidMoves(string, bool);
};

#endif
