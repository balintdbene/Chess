#ifndef __ROOK_H__
#define __ROOK_H__

#include"move.h"
#include"piece.h"
#include<string>

class Rook: public Piece{
	public:
	Rook(std::string team,Board*);
	private:
	vector<Move> getValidMoves(std::string, bool);
};

#endif
