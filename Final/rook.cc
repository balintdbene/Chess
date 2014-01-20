#include"rook.h"
#include"move.h"
#include<string>
#include<iostream>
using std::cout;
using std::endl;
using std::string;

Rook::Rook(string team,Board* chessboard){	//constructor for rook
	value = 5;
	this->chessboard = chessboard;
	this->team = team;
	if(team == "Black"){	
		type = 'r';
	}else{
		type = 'R';
	}
	underAttack = false;
	hasMoved = false;
}


vector<Move> Rook::getValidMoves(string location,bool moving){	//returns the valid moves of the rook
	vector<Move> validMoves;
	int numValidMoves = 0;
	string checkLocation = "  ";
	
	for(int i=0;i < 4; i++){
			checkLocation[0] = location[0];
			checkLocation[1] = location[1];
		for(int j =1; j < 8; j++){		
			if(i%2 == 0){
				checkLocation[0] = location[0] + (1-i)*j;
			}else{
				checkLocation[1] = location[1] + (2-i)*j;
			}
			if(validMove(location,checkLocation,moving)){
				validMoves.push_back(setMove(location,checkLocation,chessboard));
				if(validMoves[numValidMoves].capType != ' '){
					numValidMoves++;
					break;//Cannot move farther if we catch a piece
				}
				numValidMoves++;
			}else{
				break;//Cannot move farther once an invalid move is encountered
			}
		}
	}
	return validMoves;
}
