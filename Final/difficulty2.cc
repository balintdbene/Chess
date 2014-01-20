#include"move.h"
#include"difficulty2.h"
#include<time.h>
#include<stdlib.h>
Difficulty2::Difficulty2(Board* chessboard, const string& team){
	this->chessboard = chessboard;
	this->team = team;
}

Move Difficulty2::getMove(){
	string notTeam;
	if(team == "White"){
		notTeam = "Black";
	}else{
		notTeam = "White";
	}
	srand(time(NULL));
	vector<Move> possibleChecks;
	vector<Move> possibleAttacks;
	vector<Move> possibleMoves;
	vector<Move> toAdd;
	vector<Move> addAttacks;
	Move toDo;
	bool foundCheckmate = false;
	int numAttacks = 0;
	int numChecks = 0;
	int numMoves = 0;
	int doRow = 0;
	int doColumn = 0;
	int endColumn = 0;
	int endRow = 0;
	chessboard->setAttacks();//this may be critical or it may be unnecessary
	for(int i = 0; i < 8; i++){
		for(int j =0; j < 8; j++){
			if(chessboard->theBoard[i][j].piece != NULL){
				if(chessboard->theBoard[i][j].piece->team == team){
					string location = "  ";
					location[0] = j+97;
					location[1] = (8-i)+48;
					//Put all valid moves in possibleMoves
					toAdd = chessboard->theBoard[i][j].piece->getValidMoves(location,false);
					for(vector<Move>::iterator k = toAdd.begin(); k != toAdd.end(); k++){
						possibleMoves.push_back(*k);
							numMoves++;
							chessboard->doMove(*k);
							chessboard->setAttacks();
							//Do checkmate if possible
							if(chessboard->gameStatus(notTeam)=="checkmate"){
								toDo = *k;
								foundCheckmate = true;
							}
							//put all valid moves which cuse check in possibleChecks
							if(chessboard->gameStatus(notTeam)=="check"){
								possibleChecks.push_back(*k);
								numChecks++;
							}
							chessboard->undoMove(*k);
							chessboard->setAttacks();
					}
					addAttacks = chessboard->theBoard[i][j].piece->canAttack;
					//Put all valid captures in possibleAttacks
					for(vector<Move>::iterator l = addAttacks.begin(); l != addAttacks.end(); l++){
						for(vector<Move>::iterator m = toAdd.begin(); m != toAdd.end(); m++){
							if(*l == *m){
								possibleAttacks.push_back(*l);
								numAttacks++;
							}
						}
					}	
				}
			}
		}
	}
	if(foundCheckmate){
		return toDo;
	}
	int random;
	if(numAttacks != 0){
		random = rand()%numAttacks;
		toDo = possibleAttacks[random];
		doRow = 8-(toDo.start[1]-48);
		doColumn = toDo.start[0]-97;
		endRow = 8-(toDo.end[1]-48);
		endColumn = toDo.end[0]-97;
		toDo.thisHasMoved = chessboard->theBoard[doRow][doColumn].piece->hasMoved;
		if(chessboard->theBoard[endRow][endColumn].piece != NULL){
			toDo.capturedHasMoved = chessboard->theBoard[endRow][endColumn].piece->hasMoved;
		}
		chessboard->theBoard[doRow][doColumn].piece->hasMoved = true;
		return possibleAttacks[random];
	}
	if(numChecks !=0){
		random = rand()%numChecks;
		toDo = possibleChecks[random];
		doRow = 8-(toDo.start[1]-48);
		doColumn = toDo.start[0]-97;
		endRow = 8-(toDo.end[1]-48);
		endColumn = toDo.end[0]-97;
		toDo.thisHasMoved = chessboard->theBoard[doRow][doColumn].piece->hasMoved;
		if(chessboard->theBoard[endRow][endColumn].piece != NULL){
			toDo.capturedHasMoved = chessboard->theBoard[endRow][endColumn].piece->hasMoved;
		}
		chessboard->theBoard[doRow][doColumn].piece->hasMoved = true;
		return possibleChecks[random];
	}
	random = rand()%numMoves;
	toDo = possibleMoves[random];
	doRow = 8-(toDo.start[1]-48);
	doColumn = toDo.start[0]-97;
	endRow = 8-(toDo.end[1]-48);
	endColumn = toDo.end[0]-97;
	toDo.thisHasMoved = chessboard->theBoard[doRow][doColumn].piece->hasMoved;
	if(chessboard->theBoard[endRow][endColumn].piece != NULL){
		toDo.capturedHasMoved = chessboard->theBoard[endRow][endColumn].piece->hasMoved;
	}
	chessboard->theBoard[doRow][doColumn].piece->hasMoved = true;
	return toDo;
}
