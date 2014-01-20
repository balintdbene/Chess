#include"move.h"
#include"piece.h"
#include"board.h"

#include<iostream>

using namespace std;

Move Piece::setMove(string location,string checkLocation,Board* chessboard){
	Move toDo;
	toDo.start = location;
	toDo.end = checkLocation;
	bool isPawn = false;
	//No need for this loops we can simply conver the string to array locations...
	for(int i = 0; i < 8; i++){
		for(int j= 0; j < 8; j++){
			if(chessboard->theBoard[i][j].location == location){
				toDo.thisHasMoved = chessboard->theBoard[i][j].piece->hasMoved;
			}
			if(chessboard->theBoard[i][j].location == checkLocation){
				if(chessboard->theBoard[i][j].piece != NULL){
					toDo.capturedHasMoved = chessboard->theBoard[i][j].piece->hasMoved;
					toDo.capType = chessboard->theBoard[i][j].piece->type;
					toDo.capLocation = checkLocation;
				}else{
					toDo.capType = ' ';
					toDo.capLocation = "  ";
				}
			}
		}
	}
	return toDo;
}


//returns whether a potential move is valid based on the rules of chess, independant to how a piece is allowed to move
bool Piece::validMove(string startToCheck, string endToCheck, bool moving){
	int startRow = 8-(startToCheck[1]-48);
	int startColumn = startToCheck[0]-97;
	int endRow = 8-(endToCheck[1]-48);
	int endColumn = endToCheck[0]-97;

	if(chessboard->validLocation(endToCheck)){							//if the move is to a location ON the board
		if(chessboard->theBoard[endRow][endColumn].piece == NULL){				//if moving to an empty square
			return moving == false ? hypothesis(startRow, startColumn, endRow, endColumn) : true;
		}else if(chessboard->theBoard[endRow][endColumn].piece->team != team){			//if not attack same team
			return moving == false ? hypothesis(startRow, startColumn, endRow, endColumn) : true;
		}
	}
	return false;
}

//checks if a potential move will put the king of the piece thats moving into check
bool Piece::hypothesis(int sR, int sC, int eR, int eC){
	bool check = true;
	Piece* temp = NULL;
	Piece* hyp = chessboard->theBoard[sR][sC].piece;			//the board is set up in a hypothetical situation
	chessboard->theBoard[sR][sC].piece = NULL;
	if(chessboard->theBoard[eR][eC].piece != NULL){				//take off any captured piece
		temp = chessboard->theBoard[eR][eC].piece;
		chessboard->theBoard[eR][eC].piece = NULL;
	}
	chessboard->theBoard[eR][eC].piece = hyp;
	chessboard->setAttacks();
	for(int i = 0; i < 8; i++){						//checks to see if the king is in check
		for(int j = 0; j < 8; j++){
			if(chessboard->theBoard[i][j].piece == NULL) continue;
			if(chessboard->theBoard[i][j].piece == this) continue;
			vector<Move> vAttack = chessboard->theBoard[i][j].piece->canAttack;
			if(vAttack.empty()) continue;
			for(vector<Move>::iterator k = vAttack.begin(); k != vAttack.end(); k++){
				if(k->capType == 'k' && team == "Black") check = false;
				if(k->capType == 'K' && team == "White") check = false;
			}
		}
	}
	chessboard->theBoard[sR][sC].piece = hyp;				//puts the board back to original position
	chessboard->theBoard[eR][eC].piece = NULL;
	if(temp != NULL) chessboard->theBoard[eR][eC].piece = temp;
	chessboard->setAttacks();
	return check;
}
