#include"move.h"
#include"bishop.h"
#include<string>
//#include"board.h"

using std::string;

Bishop::Bishop(string team,Board* chessboard){		//constructor for bishop
	value = 3;
	this->chessboard = chessboard;
	this->team = team;
	if(team == "Black"){
		type = 'b';
	}else{
		type = 'B';
	}
	underAttack = false;
	hasMoved = false;
}

vector<Move> Bishop::getValidMoves(string location, bool moving){	//returns a vector of valid moves based on the rules of chess and of how
	vector<Move> validMoves;					//a bishop is allowed to move
	int numValidMoves = 0;
	string checkLocation = "  ";
	//We have four for loops, one for each angle the bishop can move on
	//Going Down and right
	for(int i = 1; i < 8;i++){
		checkLocation[0] = location[0] + i;
		checkLocation[1] = location[1] + i;
		if(validMove(location,checkLocation, moving)){
			validMoves.push_back(setMove(location,checkLocation,chessboard));
			if(validMoves[numValidMoves].capType != ' '){
				numValidMoves++;
				break;//Cannot move farther if we capture a piece
			}
			numValidMoves++;
		}else{
			break;//If a move is invalid then we can't go father
		}
	}
	//Going Down and left
	for(int i = 1; i < 8;i++){
		checkLocation[0] = location[0] - i;
		checkLocation[1] = location[1] + i;
		if(validMove(location,checkLocation, moving)){
			validMoves.push_back(setMove(location,checkLocation,chessboard));
			if(validMoves[numValidMoves].capType != ' '){
				numValidMoves++;
				break;//Cannot move farther if we capture a piece
			}
			numValidMoves++;
		}else{
			break;//If a move is invalid then we can't go father
		}
	}
	//Going up and right
	for(int i = 1; i < 8;i++){
		checkLocation[0] = location[0] + i;
		checkLocation[1] = location[1] - i;
		if(validMove(location,checkLocation, moving)){
			validMoves.push_back(setMove(location,checkLocation,chessboard));
			if(validMoves[numValidMoves].capType != ' '){
				numValidMoves++;
				break;//Cannot move farther if we capture a piece
			}
			numValidMoves++;
		}else{
			break;//If a move is invalid then we can't go father
		}
	}
	//Going up and left
	for(int i = 1; i < 8;i++){
		checkLocation[0] = location[0] - i;
		checkLocation[1] = location[1] - i;
		if(validMove(location,checkLocation, moving)){
			validMoves.push_back(setMove(location,checkLocation,chessboard));
			if(validMoves[numValidMoves].capType != ' '){
				numValidMoves++;
				break;//Cannot move farther if we capture a piece
			}
			numValidMoves++;
		}else{
			break;//If a move is invalid then we can't go father
		}
	}
	return validMoves;
}
