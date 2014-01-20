#include"pawn.h"
//#include"piece.h"
#include <string>
#include"board.h"
#include<iostream>

using namespace std;

Pawn::Pawn(string team,Board* chessboard){	//constructor for pawn
	value = 1;
	left = 0;
	right = 0;
	this->chessboard = chessboard;
	this->team = team;
	if(team == "Black"){
		type = 'p';
	}else{
		type = 'P';
	}
	underAttack = false;
	hasMoved = false;
}
vector<Move> Pawn::getValidMoves(string location, bool moving){
	vector<Move> validMoves;
	string checkLocation = "  ";
	int direction = team == "White" ? -1 : 1;
	int rowCheck;
	int columnCheck;
	int numMoves = 0;
	//Pawn has a limited number of moves so they're hardcoded
	//X
	//O
	checkLocation[0] = location[0];
	checkLocation[1] = location[1]-direction;
	if(validMove(location,checkLocation,moving)){
		//check location is blank as pawn can't capture straight ahead
		rowCheck = 8-(checkLocation[1]-48);
		columnCheck = checkLocation[0]-97;
		if(chessboard->theBoard[rowCheck][columnCheck].piece == NULL){
			if(team == "White" && rowCheck == 0){//due for a promotion
				for(int k = 0; k < 4; k++){
					validMoves.push_back(setMove(location,checkLocation,chessboard));
					if(k==0){
						validMoves[numMoves].promotedTo = 'Q';
					}else if(k==1){
						validMoves[numMoves].promotedTo = 'N';
					}else if(k==2){
						validMoves[numMoves].promotedTo = 'R';
					}else if(k==3){
						validMoves[numMoves].promotedTo = 'B';
					}
					numMoves++;
				}
			}else if(team == "Black" && rowCheck == 7){//due for a promotion
				for(int k = 0; k < 4; k++){
					validMoves.push_back(setMove(location,checkLocation,chessboard));
					if(k==0){
						validMoves[numMoves].promotedTo = 'q';
					}else if(k==1){
						validMoves[numMoves].promotedTo = 'n';
					}else if(k==2){
						validMoves[numMoves].promotedTo = 'r';
					}else if(k==3){
						validMoves[numMoves].promotedTo = 'b';
					}
					numMoves++;
				}
			}else{
			validMoves.push_back(setMove(location,checkLocation,chessboard));
			numMoves++;
			
			//X
			//X
			//O
				if(!hasMoved){
					checkLocation[0] = location[0];
					checkLocation[1] = location[1]-(2*direction);
					if(validMove(location,checkLocation,moving)){
						//again check the location is blank
						rowCheck+=direction;
						if(chessboard->theBoard[rowCheck][columnCheck].piece == NULL){
							validMoves.push_back(setMove(location,checkLocation,chessboard));
						}
						numMoves++;
					}
				}
			}
		}
	}
	//en passant
	if((left == 1 || right == 1) && !moving){
		string cap = "  ";
		cap[1] = location[1];
		checkLocation[1] = location[1]-direction;
		if(left == 1){
			cap[0] = location[0] - 1;
			checkLocation[0] = location[0] - 1;
		}else if(right == 1){
			cap[0] = location[0] + 1;
			checkLocation[0] = location[0] + 1;
		}
		if(validMove(location, checkLocation, moving)){
			validMoves.push_back(setMove(location, checkLocation, chessboard));
			validMoves[numMoves].capLocation = cap;
			if(team == "White") validMoves[numMoves].capType = 'p';
			if(team == "Black") validMoves[numMoves].capType = 'P';
			numMoves++;
		}
	}

	//CAPTURING MOVES
	//X_
	//_O
	checkLocation[0] = location[0]-1;
	checkLocation[1] = location[1]-direction;
	if(validMove(location,checkLocation,moving)){
		//check the location has a piece (validMove ensures it's an opponent
		rowCheck = 8-(checkLocation[1]-48);
		columnCheck = checkLocation[0]-97;
		if(chessboard->theBoard[rowCheck][columnCheck].piece != NULL){
			if(team == "White" && rowCheck == 0){//due for a promotion
				for(int k = 0; k < 4; k++){
					validMoves.push_back(setMove(location,checkLocation,chessboard));
					if(k==0){
						validMoves[numMoves].promotedTo = 'Q';
					}else if(k==1){
						validMoves[numMoves].promotedTo = 'N';
					}else if(k==2){
						validMoves[numMoves].promotedTo = 'R';
					}else if(k==3){
						validMoves[numMoves].promotedTo = 'B';
					}
					numMoves++;
				}
			}else if(team == "Black" && rowCheck == 7){//due for a promotion
				for(int k = 0; k < 4; k++){
					validMoves.push_back(setMove(location,checkLocation,chessboard));
					if(k==0){
						validMoves[numMoves].promotedTo = 'q';
					}else if(k==1){
						validMoves[numMoves].promotedTo = 'n';
					}else if(k==2){
						validMoves[numMoves].promotedTo = 'r';
					}else if(k==3){
						validMoves[numMoves].promotedTo = 'b';
					}
					numMoves++;
				}
			}else{
				validMoves.push_back(setMove(location,checkLocation,chessboard));
				numMoves++;
			}
		}
	}
	//_X
	//O_
	checkLocation[0] = location[0]+1;
	checkLocation[1] = location[1]-direction;
	if(validMove(location,checkLocation,moving)){
		//check the location has a piece (validMove ensures it's an opponent)
		rowCheck = 8-(checkLocation[1]-48);
		columnCheck = checkLocation[0]-97;
		if(chessboard->theBoard[rowCheck][columnCheck].piece != NULL){
			if(team == "White" && rowCheck == 0){//due for a promotion
				for(int k = 0; k < 4; k++){
					validMoves.push_back(setMove(location,checkLocation,chessboard));
					if(k==0){
						validMoves[numMoves].promotedTo = 'Q';
					}else if(k==1){
						validMoves[numMoves].promotedTo = 'N';
					}else if(k==2){
						validMoves[numMoves].promotedTo = 'R';
					}else if(k==3){
						validMoves[numMoves].promotedTo = 'B';
					}
					numMoves++;
				}
			}else if(team == "Black" && rowCheck == 7){//due for a promotion
				for(int k = 0; k < 4; k++){
					validMoves.push_back(setMove(location,checkLocation,chessboard));
					if(k==0){
						validMoves[numMoves].promotedTo = 'q';
					}else if(k==1){
						validMoves[numMoves].promotedTo = 'n';
					}else if(k==2){
						validMoves[numMoves].promotedTo = 'r';
					}else if(k==3){
						validMoves[numMoves].promotedTo = 'b';
					}
					numMoves++;
				}
			}else{
				validMoves.push_back(setMove(location,checkLocation,chessboard));
				numMoves++;
			}
		}
	}
	return validMoves;
}
