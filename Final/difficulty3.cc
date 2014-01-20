#include"difficulty3.h"
#include"move.h"
#include<time.h>
#include<stdlib.h>

Difficulty3::Difficulty3(Board* chessboard, const string& team){
	this->chessboard = chessboard;
	this->team = team;
}

Move Difficulty3::getMove(){
	srand(time(NULL));
	string notTeam;
	if(team == "White"){
		notTeam = "Black";
	}else{
		notTeam = "White";
	}
	vector<Move> possibleAttacks;
	vector<Move> possibleChecks;
	vector<Move> possibleMoves;
	vector<Move> possibleDodges;
	vector<Move> toAdd;
	vector<Move> addAttacks;
	Move toDo;
	int numAttacks = 0;
	int numMoves = 0;
	int numDodges = 0;
	int numChecks = 0;
	int doRow = 0;
	int doColumn = 0;
	int endRow = 0;
	int endColumn = 0;
	bool underAttackBefore = false;
	bool foundCheckmate = false;
	chessboard->setAttacks();//this may be critical or it may be unnecessary
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(chessboard->theBoard[i][j].piece != NULL){
				if(chessboard->theBoard[i][j].piece->team == team){
					underAttackBefore = chessboard->theBoard[i][j].piece->underAttack;
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
						//Do checkmate if ever possible
						if(chessboard->gameStatus(notTeam)=="checkmate"){
							toDo = *k;
							foundCheckmate = true;
						}
						//put all valid moves which cause check in possibleChecks
						if(chessboard->gameStatus(notTeam)=="check"){
							possibleChecks.push_back(*k);
							numChecks++;
						}
						//put all dodges in possibleDodges
						endRow = 8-(k->end[1]-48);
						endColumn = k->end[0]-97;
						if(underAttackBefore && !chessboard->theBoard[endRow][endColumn].piece->underAttack){
							possibleDodges.push_back(*k);
							numDodges++;
						}
						chessboard->undoMove(*k);
						chessboard->setAttacks();
					}
					//Put all valid captures in possibleAttacks
					addAttacks = chessboard->theBoard[i][j].piece->canAttack;
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
	//MAY NOT NEED TO SET HAS MOVED VALUES IN ANYTHING IF SET MOVES DOES IT RIGHT
	int random;
	if(numDodges != 0){
		random = rand()%numDodges;
		toDo = possibleDodges[random];
		doRow = 8-(toDo.start[1]-48);
		doColumn = toDo.start[0]-97;
		endRow = 8-(toDo.end[1]-48);
		endColumn = toDo.end[0]-97;
		toDo.thisHasMoved = chessboard->theBoard[doRow][doColumn].piece->hasMoved;
		if(chessboard->theBoard[endRow][endColumn].piece != NULL){
			toDo.capturedHasMoved = chessboard->theBoard[endRow][endColumn].piece->hasMoved;
		}
		chessboard->theBoard[doRow][doColumn].piece->hasMoved = true;
		return possibleDodges[random];
	}
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
	if(numChecks != 0){
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
