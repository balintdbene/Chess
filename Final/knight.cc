#include"move.h"
#include"knight.h"
#include<string>
#include"board.h"
#include<iostream>

using std::cout;
using std::cerr;
using std::endl;
using std::string;

Knight::Knight(string team,Board* chessboard){	//constructor for the Knight
	value = 3;
	this->chessboard = chessboard;
	this->team = team;
	if(team == "Black"){
		type = 'n';
	}else{
		type = 'N';
	}
	underAttack = false;
	hasMoved = false;
}

vector<Move> Knight::getValidMoves(string location,bool moving){
	vector<Move> validMoves;
	int numValidMoves = 0;
	//The knight as 8 possible moves at any given time
	//No easy way to loop thorugh them so we check them individually
	string checkLocation = "  ";
	//XX
	//_X
	//_O
	checkLocation[0] = location[0]-1;
	checkLocation[1] = location[1]-2;
	if(validMove(location,checkLocation,moving)){
		validMoves.push_back(setMove(location,checkLocation,chessboard));
		numValidMoves++;
	}
	//XX
	//X_
	//O_
	checkLocation[0] = location[0]+1;
	checkLocation[1] = location[1]-2;
	if(validMove(location,checkLocation,moving)){
		validMoves.push_back(setMove(location,checkLocation,chessboard));
		numValidMoves++;
	}
	//O_
	//X_
	//XX
	checkLocation[0] = location[0]+1;
	checkLocation[1] = location[1]+2;
	if(validMove(location,checkLocation,moving)){
		validMoves.push_back(setMove(location,checkLocation,chessboard));
		numValidMoves++;
	}
	//_O
	//_X
	//XX
	checkLocation[0] = location[0]-1;
	checkLocation[1] = location[1]+2;
	if(validMove(location,checkLocation,moving)){
		validMoves.push_back(setMove(location,checkLocation,chessboard));
		numValidMoves++;	
	}
	//X__
	//XXO
	checkLocation[0] = location[0]-2;
	checkLocation[1] = location[1]-1;
	if(validMove(location,checkLocation,moving)){
		validMoves.push_back(setMove(location,checkLocation,chessboard));
		numValidMoves++;
	}

	//XXO
	//X__
	checkLocation[0] = location[0]-2;
	checkLocation[1] = location[1]+1;
	if(validMove(location,checkLocation,moving)){
		validMoves.push_back(setMove(location,checkLocation,chessboard));
		numValidMoves++;
	}
	//OXX
	//__X
	checkLocation[0] = location[0]+2;
   checkLocation[1] = location[1]+1;
	if(validMove(location,checkLocation,moving)){
		validMoves.push_back(setMove(location,checkLocation,chessboard));
		numValidMoves++;	
	}
	//__X
	//OXX
	checkLocation[0] = location[0]+2;
	checkLocation[1] = location[1]-1;
	if(validMove(location,checkLocation,moving)){
		validMoves.push_back(setMove(location,checkLocation,chessboard));
		numValidMoves++;
	}
	return validMoves;
}
