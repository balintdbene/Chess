#ifndef __PAWN_H__
#define __PAWN_H__

#include"move.h"
#include"piece.h"
#include<string>
#include<vector>

//class Piece;

class Pawn: public Piece{
	public:
	Pawn(std::string team, Board*);
	private:
	std::vector<Move> getValidMoves(std::string, bool);
};

#endif
