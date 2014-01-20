#ifndef __QUEEN_H__
#define __QUEEN_H__

#include"move.h"
#include"piece.h"
#include<string>
//#include"board.h"

class Queen: public Piece{
	public:
	Queen(std::string,Board*);
	private:
	vector<Move> getValidMoves(std::string, bool);
};
#endif
