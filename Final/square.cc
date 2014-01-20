#include"move.h"
#include"square.h"
#include<iostream>
#include"king.h"
#include"queen.h"
#include"knight.h"
#include"bishop.h"
#include"rook.h"
#include"pawn.h"

Square::Square(){	//constructor for square
	piece = NULL;
	location = "  ";
}

Square::~Square(){	//destructor for square, responsible for calling the destructor of any piece on it
	delete piece;
	piece = NULL;
}

void Square::notifyDisplay(TextDisplay& td){		//locatation goes from "a8" to "h1" and must follow this format, does not follow array indices
	char symbol;
	if(piece != NULL){
		symbol = piece->type;
	}else if(location[0] % 2 == 1){		//if odd row
		if(location[1] % 2 == 1)		//if odd column
			symbol = '_';
		else					//if even column
			symbol = ' ';
	}else{					//if even row
		if(location[1] % 2 == 1)		//if odd column
			symbol = ' ';
		else					//if even column
			symbol = '_';
	}
	td.notify(8-(location[1]-48), location[0] - 97, symbol);
}

void Square::generatePiece(char type,Board* chessboard){		//generates a piece of any type, either team
	switch(type){
		case 'B':
			piece = new Bishop("White",chessboard);
			break;
		case 'K':
			piece = new King("White",chessboard);
			break;
		case 'N':
			piece = new Knight("White",chessboard);
			break;
		case 'P':
			piece = new Pawn("White",chessboard);
			break;
		case 'Q':
			piece = new Queen("White",chessboard);
			break;
		case 'R':
			piece = new Rook("White",chessboard);
			break;
		case 'b':
			piece = new Bishop("Black",chessboard);
			break;
		case 'k':
			piece = new King("Black",chessboard);
			break;
		case 'n':
			piece = new Knight("Black",chessboard);
			break;
		case 'p':
			piece = new Pawn("Black",chessboard);
			break;
		case 'q':
			piece = new Queen("Black",chessboard);
			break;
		case 'r':
			piece = new Rook("Black",chessboard);
			break;
	}
}
