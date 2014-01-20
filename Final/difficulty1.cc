#include"difficulty1.h"
#include<stdlib.h>
#include<time.h>

Difficulty1::Difficulty1(Board* chessboard, const string& team){
	this->chessboard = chessboard;
	this->team = team;
}

Move Difficulty1::getMove(){
	srand(time(NULL));
	vector<Move> possibleMoves;
	vector<Move> toAdd;
	Move toDo;
	int doRow;
	int doColumn;
	int numOptions = 0;
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(chessboard->theBoard[i][j].piece != NULL){
				if(chessboard->theBoard[i][j].piece->team == team){
					string location = "  ";
					location[0] = j + 97;
					location[1] = (8-i)+48;
					toAdd = chessboard->theBoard[i][j].piece->getValidMoves(location,false);
					for(vector<Move>::iterator k = toAdd.begin(); k != toAdd.end(); k++){
						possibleMoves.push_back(*k);
						numOptions++;
					}
				}
			}
		}
	}
	int random = 0;
	if(numOptions != 0){
		random = rand()%numOptions;
	}
	toDo = possibleMoves[random];
	doRow = 8-(toDo.start[1]-48);
	doColumn = toDo.start[0]-97;
	int endRow = 8-(toDo.end[1]-48);
	int endColumn = toDo.end[0]-97;
	toDo.thisHasMoved = chessboard->theBoard[doRow][doColumn].piece->hasMoved;
	if(chessboard->theBoard[endRow][endColumn].piece != NULL){
		toDo.capturedHasMoved = chessboard->theBoard[endRow][endColumn].piece->hasMoved;
	}
	chessboard->theBoard[doRow][doColumn].piece->hasMoved = true;
	return toDo;
}
