#ifndef __SQUARE_H__
#define __SQUARE_H__
#include<string>
#include"piece.h"
#include "textdisplay.h"
using std::string;

class Square{
	public:
	Square();
	~Square();
	Piece* piece;
	void notifyDisplay(TextDisplay&); //Notifies the TextDisplay about its condition
	string location;		//must be in format: "e5"
	void generatePiece(char type,Board* chessboard);
};

#endif
