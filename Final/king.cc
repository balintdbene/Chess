#include"king.h"
#include<string>
#include"board.h"

using std::string;


King::King(string team,Board* chessboard){	//constructor for a king Piece
	value = 200;
	this->chessboard = chessboard;
	this->team = team;
	if(team == "Black"){
		type = 'k';
	}else{
		type = 'K';
	}
	underAttack = false;
	hasMoved = false;
	checkingCastles = false;
}

vector<Move> King::validCastles(string location){	//checks for valid castling
	int row = 8-(location[1]-48);
	int column = location[0]-97;
	vector<Move> castles;
		checkingCastles = true;
		string notTeam;
		if(team == "White"){
			notTeam = "Black";
		}else{
			notTeam = "White";
		}
		string status;
		Move topRightCastle; topRightCastle.start = "e8"; topRightCastle.end = "g8"; topRightCastle.castling = true;
		Move topLeftCastle; topLeftCastle.start = "e8"; topLeftCastle.end = "c8"; topLeftCastle.castling = true;
		Move bottomRightCastle; bottomRightCastle.start = "e1"; bottomRightCastle.end = "g1"; bottomRightCastle.castling = true;
		Move bottomLeftCastle; bottomLeftCastle.start = "e1"; bottomLeftCastle.end = "c1"; bottomLeftCastle.castling = true;
		Piece* topRightRook = chessboard->theBoard[0][7].piece;
		Piece* topLeftRook = chessboard->theBoard[0][0].piece;
		Piece* bottomRightRook = chessboard->theBoard[7][7].piece;
		Piece* bottomLeftRook = chessboard->theBoard[7][0].piece;
		Move topRight1; topRight1.start = "e8"; topRight1.end = "f8";
		Move topRight2; topRight2.start = "e8"; topRight2.end = "g8";
		Move topLeft1; topLeft1.start = "e8"; topLeft1.end = "d8";
		Move topLeft2; topLeft2.start = "e8"; topLeft2.end = "c8";
		Move bottomRight1; bottomRight1.start = "e1"; bottomRight1.end = "f1";
		Move bottomRight2; bottomRight2.start = "e1"; bottomRight2.end = "g1";
		Move bottomLeft1; bottomLeft1.start = "e1"; bottomLeft1.end = "d1";
		Move bottomLeft2; bottomLeft2.start = "e1"; bottomLeft2.end = "c1";
		if(location == "e1" || location == "e8"){
			if(!hasMoved){
				if(chessboard->gameStatus(team) != "check"){
					if(row == 0 && team == "Black"){//Black King
						if(topRightRook != NULL && topRightRook->type == 'r' && !topRightRook->hasMoved){
							if(chessboard->theBoard[row][column+1].piece == NULL && chessboard->theBoard[row][column+2].piece == NULL){
								//GENERATING KINGS TO CHECK FOR CHECK
								chessboard->theBoard[row][column+1].generatePiece('k',chessboard);
								chessboard->theBoard[row][column+2].generatePiece('k',chessboard);
								chessboard->setAttacks();
								status = chessboard->gameStatus(team);
								if(status != "check" && status != "checkmate"){
									castles.push_back(topRightCastle);
								}
								delete chessboard->theBoard[row][column+1].piece;
								chessboard->theBoard[row][column+1].piece = NULL;
								delete chessboard->theBoard[row][column+2].piece;
								chessboard->theBoard[row][column+2].piece = NULL;
								chessboard->setAttacks();
							}
						}
						if(topLeftRook != NULL && topLeftRook->type == 'r' && !topLeftRook->hasMoved){
							if(chessboard->theBoard[row][column-1].piece == NULL && chessboard->theBoard[row][column-2].piece == NULL){
								//GENERATING KINGS TO CHECK FOR CHECK
								chessboard->theBoard[row][column-1].generatePiece('k',chessboard);
								chessboard->theBoard[row][column-2].generatePiece('k',chessboard);	
								chessboard->setAttacks();
								status = chessboard->gameStatus(team);
								if(status != "check" && status != "checkmate"){
									castles.push_back(topLeftCastle);
								}
								delete chessboard->theBoard[row][column-1].piece;
								chessboard->theBoard[row][column-1].piece = NULL;
								delete chessboard->theBoard[row][column-2].piece;
								chessboard->theBoard[row][column-2].piece = NULL;
								
								chessboard->setAttacks();
							}
						}
					}
					if(row == 7 && team == "White"){//White King
						if(bottomRightRook != NULL && bottomRightRook->type == 'R' && !bottomRightRook->hasMoved){
							if(chessboard->theBoard[row][column+1].piece == NULL && chessboard->theBoard[row][column+2].piece == NULL){
								//GENERATING KINGS TO CHECK FOR CHECK
								chessboard->theBoard[row][column+1].generatePiece('K',chessboard);
								chessboard->theBoard[row][column+2].generatePiece('K',chessboard);
								chessboard->setAttacks();
								status = chessboard->gameStatus(team);
								if(status != "check" && status != "checkmate"){
									castles.push_back(bottomRightCastle);
								}
								delete chessboard->theBoard[row][column+1].piece;
								chessboard->theBoard[row][column+1].piece = NULL;
								delete chessboard->theBoard[row][column+2].piece;
								chessboard->theBoard[row][column+2].piece = NULL;
								chessboard->setAttacks();
							}
						}
						if(bottomLeftRook != NULL && bottomLeftRook->type == 'R' && !bottomLeftRook->hasMoved){
							if(chessboard->theBoard[row][column-1].piece == NULL && chessboard->theBoard[row][column-2].piece == NULL){
								//GENERATING KINGS TO CHECK FOR CHECK
								chessboard->theBoard[row][column-1].generatePiece('K',chessboard);
								chessboard->theBoard[row][column-2].generatePiece('K',chessboard);
								chessboard->setAttacks();
								status = chessboard->gameStatus(team);
								if(status != "check" && status != "checkmate"){
									castles.push_back(bottomLeftCastle);
								}
								delete chessboard->theBoard[row][column-1].piece;
								chessboard->theBoard[row][column-1].piece = NULL;
								delete chessboard->theBoard[row][column-2].piece;
								chessboard->theBoard[row][column-2].piece = NULL;
							
								chessboard->setAttacks();
							}
						}
					}
				}
			}
	}
	checkingCastles = false;
		return castles;
}
vector<Move> King::getValidMoves(string location,bool moving){	//returns a vector of valid moves of the king based on the situation of the board
	vector<Move> validMoves;
	int numValidMoves = 0;
	string checkLocation = "  ";
	if(!checkingCastles && !moving){
		validMoves = validCastles(location);
	}
	//King can move once in any of eight direction so we check them individually
	//Up
	checkLocation[0] = location[0];
	checkLocation[1] = location[1] - 1;
	if(validMove(location,checkLocation,moving)){
		validMoves.push_back(setMove(location,checkLocation,chessboard));
	}
	//Up and right
	checkLocation[0] = location[0] + 1;
	checkLocation[1] = location[1] - 1;
	if(validMove(location,checkLocation,moving)){
		validMoves.push_back(setMove(location,checkLocation,chessboard));
	}
	//Right
	checkLocation[0] = location[0] + 1;
	checkLocation[1] = location[1];
	if(validMove(location,checkLocation,moving)){
		validMoves.push_back(setMove(location,checkLocation,chessboard));
	}
	//down and right
	checkLocation[0] = location[0] + 1;
	checkLocation[1] = location[1] + 1;
	if(validMove(location,checkLocation,moving)){
		validMoves.push_back(setMove(location,checkLocation,chessboard));
	}
	//down
	checkLocation[0] = location[0];
	checkLocation[1] = location[1] + 1;
	if(validMove(location,checkLocation,moving)){
		validMoves.push_back(setMove(location,checkLocation,chessboard));
	}
	//down left
	checkLocation[0] = location[0] - 1;
	checkLocation[1] = location[1] + 1;
	if(validMove(location,checkLocation,moving)){
		validMoves.push_back(setMove(location,checkLocation,chessboard));
	}
	//left
	checkLocation[0] = location[0] - 1;
	checkLocation[1] = location[1];
	if(validMove(location,checkLocation,moving)){
		validMoves.push_back(setMove(location,checkLocation,chessboard));
	}
	//left and up
	checkLocation[0] = location[0] - 1;
	checkLocation[1] = location[1] - 1;
	if(validMove(location,checkLocation,moving)){
		validMoves.push_back(setMove(location,checkLocation,chessboard));
	}
	return validMoves;
}
