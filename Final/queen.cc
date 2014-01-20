#include"queen.h"
#include<string>
//#include"board.h"

using std::string;

Queen::Queen(string team,Board* chessboard){	//constructor for queen
	value = 9;
	this->chessboard = chessboard;
	this->team = team;
	if(team == "Black"){
		type = 'q';
	}else{
		type = 'Q';
	}
	underAttack = false;
	hasMoved = false;
}

vector<Move> Queen::getValidMoves(string location,bool moving){
	vector<Move> validMoves;
	int numValidMoves = 0;
	string checkLocation = "  ";
	//We have eight for loops, one for each direction the queen can move in
	//Going up
for(int i =1; i < 8; i++){
	checkLocation[0] = location[0];
	checkLocation[1] = location[1]-i;
	if(validMove(location,checkLocation,moving)){
		validMoves.push_back(setMove(location,checkLocation,chessboard));
		if(validMoves[numValidMoves].capType != ' '){
			numValidMoves++;
			break;//can't move father if we catch a piece
		}
		numValidMoves++;
	}else{
		break;//If a move is invalid we can't go farther
	}
}
	//Going up and right
	for(int i =1; i < 8; i++){
		checkLocation[0] = location[0]+i;
		checkLocation[1] = location[1]-i;
		if(validMove(location,checkLocation,moving)){
			validMoves.push_back(setMove(location,checkLocation,chessboard));
			if(validMoves[numValidMoves].capType != ' '){
				numValidMoves++;
				break;//can't move father if we catch a piece
			}
			numValidMoves++;
		}else{
			break;//If a move is invalid we can't go farther
		}
	}
	//Going right
	for(int i =1; i < 8; i++){
		checkLocation[0] = location[0]+i;
		checkLocation[1] = location[1];
		if(validMove(location,checkLocation,moving)){
			validMoves.push_back(setMove(location,checkLocation,chessboard));
			if(validMoves[numValidMoves].capType != ' '){
				numValidMoves++;
				break;//can't move father if we catch a piece
			}
			numValidMoves++;
		}else{
			break;//If a move is invalid we can't go farther
		}
	}
	//Going down and right
	for(int i =1; i < 8; i++){
		checkLocation[0] = location[0]+i;
		checkLocation[1] = location[1]+i;
		if(validMove(location,checkLocation,moving)){
			validMoves.push_back(setMove(location,checkLocation,chessboard));
			if(validMoves[numValidMoves].capType != ' '){
				numValidMoves++;
				break;//can't move father if we catch a piece
			}
			numValidMoves++;
		}else{
			break;//If a move is invalid we can't go farther
		}
	}
	//Going down
	for(int i =1; i < 8; i++){
		checkLocation[0] = location[0];
		checkLocation[1] = location[1]+i;
		if(validMove(location,checkLocation,moving)){
			validMoves.push_back(setMove(location,checkLocation,chessboard));
			if(validMoves[numValidMoves].capType != ' '){
				numValidMoves++;
				break;//can't move father if we catch a piece
			}
			numValidMoves++;
		}else{
			break;//If a move is invalid we can't go farther
		}
	}
	//Going down and left
	for(int i =1; i < 8; i++){
		checkLocation[0] = location[0]-i;
		checkLocation[1] = location[1]+i;
		if(validMove(location,checkLocation,moving)){
			validMoves.push_back(setMove(location,checkLocation,chessboard));
			if(validMoves[numValidMoves].capType != ' '){
				numValidMoves++;
				break;//can't move father if we catch a piece
			}
			numValidMoves++;
		}else{
			break;//If a move is invalid we can't go farther
		}
	}
	//Going left
	for(int i =1; i < 8; i++){
		checkLocation[0] = location[0]-i;
		checkLocation[1] = location[1];
		if(validMove(location,checkLocation,moving)){
			validMoves.push_back(setMove(location,checkLocation,chessboard));
			if(validMoves[numValidMoves].capType != ' '){
				numValidMoves++;
				break;//can't move father if we catch a piece
			}
			numValidMoves++;
		}else{
			break;//If a move is invalid we can't go farther
		}
	}
	//Going up and left
	for(int i =1; i < 8; i++){
		checkLocation[0] = location[0]-i;
		checkLocation[1] = location[1]-i;
		if(validMove(location,checkLocation,moving)){
			validMoves.push_back(setMove(location,checkLocation,chessboard));
			if(validMoves[numValidMoves].capType != ' '){
				numValidMoves++;
				break;//can't move father if we catch a piece
			}
			numValidMoves++;
		}else{
			break;//If a move is invalid we can't go farther
		}
	}
	return validMoves;
}
