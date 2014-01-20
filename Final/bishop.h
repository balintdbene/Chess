#ifndef __BISHOP_H__
#define __BISHOP_H__

#include"piece.h"
//#include"move.h"
#include<string>
//#include"board.h"

class Bishop: public Piece{
	public:
	Bishop(string,Board*);
	private:
	vector<Move> getValidMoves(string, bool);
};



#endif
