#include"board.h"
#include"piece.h"
#include"rook.h"
#include"knight.h"
#include"pawn.h"
#include"king.h"
#include"queen.h"
#include"bishop.h"
#include"textdisplay.h"
#include<iostream>
#include<string>

using namespace std;

bool Board::validLocation(string toCheckCPP){			//checks if a coordinate is within the bounds of the board
	int sizeCheck = toCheckCPP.length();
	const char* toCheck = toCheckCPP.c_str();
	if(sizeCheck == 2){
		if(97 <= toCheck[0] && toCheck[0] <= 104){
			if(49 <= toCheck[1] & toCheck[1] <= 56){
				return true;
			}
		}
	}
	return false;
}
Board::Board(TextDisplay* td){					//constructor for the board
	this->td = td;
	theBoard = new Square*[8];
	char column = '1';
	char row = 'a';
	string squareLocation = ""; 
	for(int i = 0; i < 8; i++){
		theBoard[i] = new Square[8];
		for(int j = 0; j < 8; j++){
			squareLocation += row+j;
			squareLocation += column-i+7;
			theBoard[i][j].location = squareLocation;
			squareLocation = "";
		}
	}
}

Board::~Board(){						//destructor for the board
	for(int i = 0; i < 8; i++){
		delete [] theBoard[i];				//responsible for calling the destructor of the squares
	}
	delete [] theBoard;
}
void Board::setup(){						//sets up the board with a default setup of the pieces
	//Place the pieces
	string team = "Black";
	for(int i = 0; i < 2; i++){
		if(i == 1){
			team = "White";
		}
		theBoard[i*7][0].piece = new Rook(team,this);	//parameters go here
		theBoard[i*7][1].piece = new Knight(team,this);
		theBoard[i*7][2].piece = new Bishop(team,this);
		theBoard[i*7][3].piece = new Queen(team,this);
		theBoard[i*7][4].piece = new King(team,this);
		theBoard[i*7][5].piece = new Bishop(team,this);
		theBoard[i*7][6].piece = new Knight(team,this);
		theBoard[i*7][7].piece = new Rook(team,this);	
	}
	for(int j = 0; j < 8; j++){
			theBoard[1][j].piece = new Pawn("Black",this);
			theBoard[6][j].piece = new Pawn("White",this);
	}
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			theBoard[i][j].notifyDisplay(*td);
		}
	}
}


void Board::setAttacks(){			//saves all the moves where a piece can attack another to a vector in each piece
	vector<Move> temp;			//this is done independantly to whether or not the move would put their own king in check
	bool check = false;
	int capturingRow = 0;
	int capturingColumn = 0;
	//Reset every pieces underAttack bool to false
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(theBoard[i][j].piece != NULL){
				theBoard[i][j].piece->underAttack = false;
			}
		}
	}
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(theBoard[i][j].piece != NULL){
				string start = "  ";
				start[0] = j + 97;
				start[1] = (8 - i) + 48;
				theBoard[i][j].piece->canAttack.clear();
				temp = theBoard[i][j].piece->getValidMoves(start, true); //a vector of all the moves for the piece
				if(!temp.empty()){
					for(vector<Move>::iterator k = temp.begin(); k != temp.end(); k++){	//keeps the moves that attack
						if(k->capType != ' '){
						theBoard[i][j].piece->canAttack.push_back(*k);
						capturingRow = 8-(k->end[1]-48);
						capturingColumn = k->end[0]-97;
						if(theBoard[capturingRow][capturingColumn].piece != NULL){
							theBoard[capturingRow][capturingColumn].piece->underAttack = true;
						}
						}
					}
				}
			}
		}
	}
}

string Board::gameStatus(string checkTeam){				//returns a string which describes the status of the game
	bool check = false;
	bool moveable = false;
	bool loop = true;
	bool bPeasant = false;
	bool wPeasant = false;
	Piece* pc;
	vector<Move> temp;
	for(int i = 0; i < 8 && loop; i++)				//checks the entire board or until its found that a piece of the correct team
	{								//can make a valid move, that its king is in check, and theres more than just
		for(int j = 0; j < 8 && loop; j++){			//two kings on the board
			if(check && moveable) loop = false;
			if(theBoard[i][j].piece == NULL) continue;	//if there is no piece, continue to next loop
			pc = theBoard[i][j].piece;
			if(pc->type <= 'Z' && pc->type != 'K') wPeasant = true;
			if(pc->type >= 'a' && pc->type != 'k') bPeasant = true;
			if(pc->team != checkTeam && !check){		//see if the oppenents piece is putting the king into check
				temp = pc->canAttack;
				for(vector<Move>::iterator k = temp.begin(); k != temp.end(); k++){
					if(k->capType == 'k' || k->capType == 'K') check = true;
				}
			}
			if(pc->team == checkTeam && !moveable){		//check if the player has any valid moves whatsoever
				string start = "  ";
				start[0] = j + 97;
				start[1] = (8 - i) + 48;
				temp = pc->getValidMoves(start, false);		//get the valid moves of the piece
				if(temp.size() != 0) moveable = true;
			}
		}
	}
	if(!bPeasant && !wPeasant) return "stalemate";			//if theres only two kings, it's a stalemate
	if(check && moveable) return "check";				//return the status of the game
	if(!check && moveable) return "nothing";
	if(!check && !moveable) return "stalemate";
	if(check && !moveable) return "checkmate";
}

void Board::tickPawn(){						//disables pawns' ability to en passant over time. A pawn must en passant right away
	for(int i = 0; i < 8; i++){				//if it is to en passant at all
		for(int j = 0; j < 8; j++){
			if(theBoard[i][j].piece == NULL) continue;
			Piece* pc = theBoard[i][j].piece;
			if(pc->type != 'p' && pc->type != 'P') continue;
			pc->left = max(0, pc->left - 1);
			pc->right = max(0, pc->right - 1);
		}
	}
}

void Board::doMove(Move toDo){					//does a Move passed to it; ie: moves pieces relevant to the move
	int startRow = 8-(toDo.start[1] - 48);
	int startColumn = toDo.start[0]-97;
	int endRow = 8-(toDo.end[1]-48);
	int endColumn = toDo.end[0]-97;
	int capRow = 8-(toDo.capLocation[1]-48);
	int capColumn = toDo.capLocation[0]-97;
	char type = theBoard[startRow][startColumn].piece->type;
	if((type == 'p' || type == 'P') && (startRow - endRow == 2 || startRow - endRow == -2)){	//setting en passant
		if(endColumn-1 >= 0 && theBoard[endRow][endColumn-1].piece != NULL && theBoard[endRow][endColumn-1].piece->team != theBoard[startRow][startColumn].piece->team){
			if(theBoard[endRow][endColumn-1].piece->type == 'p' || theBoard[endRow][endColumn-1].piece->type == 'P')
				theBoard[endRow][endColumn-1].piece->right += 2;
		}
		if(endColumn+1 <= 7 && theBoard[endRow][endColumn+1].piece != NULL && theBoard[endRow][endColumn+1].piece->team != theBoard[startRow][startColumn].piece->team){
			if(theBoard[endRow][endColumn+1].piece->type == 'p' || theBoard[endRow][endColumn+1].piece->type == 'P')
				theBoard[endRow][endColumn+1].piece->left += 2;
		} 
	}
	if(toDo.castling){
		delete theBoard[endRow][endColumn].piece;//Shouldn't be anythign here anyways
		theBoard[endRow][endColumn].piece = NULL;
		theBoard[endRow][endColumn].piece = theBoard[startRow][startColumn].piece;//Move king
		theBoard[startRow][startColumn].piece = NULL;
		//Move rooks hardcoded...
		if(toDo.end == "g8" || toDo.end == "g1"){//Right castles
			delete theBoard[startRow][startColumn+1].piece;//Shoudln't be anything here
			theBoard[startRow][startColumn+1].piece = NULL;
			theBoard[startRow][startColumn+1].piece = theBoard[startRow][startColumn+3].piece;//Move rook
			theBoard[startRow][startColumn+3].piece = NULL;
		}else if(toDo.end == "c1" || toDo.end == "c8"){//Left castles
	delete theBoard[startRow][startColumn-1].piece;//Shoudln't be anything here
			theBoard[startRow][startColumn-1].piece = NULL;
			theBoard[startRow][startColumn-1].piece = theBoard[startRow][startColumn-4].piece;//Move rook
			theBoard[startRow][startColumn-4].piece = NULL;
		}
		return;//all of castling is included in here and handled seperate of the other cases
	}
	if(toDo.capLocation != "  "){
		delete theBoard[capRow][capColumn].piece;
		theBoard[capRow][capColumn].piece = NULL;
	}
	theBoard[endRow][endColumn].piece = theBoard[startRow][startColumn].piece;
	theBoard[startRow][startColumn].piece = NULL;
	if(toDo.promotedTo != ' '){
		delete theBoard[endRow][endColumn].piece;
		theBoard[endRow][endColumn].piece = NULL;
		theBoard[endRow][endColumn].generatePiece(toDo.promotedTo,this);
	}
	theBoard[endRow][endColumn].piece->hasMoved = true;				//the piece has moved, therefore its true
	tickPawn();
}
void Board::undoMove(Move toUndo){
	int startRow = 8-(toUndo.start[1] - 48);
	int startColumn = toUndo.start[0] - 97;
	int endRow = 8-(toUndo.end[1]-48);
	int endColumn = toUndo.end[0]-97;
	int capRow = 8-(toUndo.capLocation[1]-48);
	int capColumn = toUndo.capLocation[0]-97;
	if(toUndo.castling){//Undoing a castle
		theBoard[startRow][startColumn].piece = theBoard[endRow][endColumn].piece;//reset king position
		theBoard[endRow][endColumn].piece = NULL;
		theBoard[startRow][startColumn].piece->hasMoved = false;//Reset kings has Moved
		if(toUndo.end == "g8" || toUndo.end == "g1"){//Right castles
			theBoard[startRow][startColumn+3].piece = theBoard[startRow][startColumn+1].piece;//Reset rook position
			theBoard[startRow][startColumn+1].piece = NULL;
			theBoard[startRow][startColumn+3].piece->hasMoved = false;
		}else if(toUndo.end == "c8" || toUndo.end == "c1"){//Left castles
			theBoard[startRow][startColumn-4].piece = theBoard[startRow][startColumn-1].piece;//reset rook position
			theBoard[startRow][startColumn-4].piece->hasMoved = false;
			theBoard[startRow][startColumn-1].piece = NULL;
		}
		return;//castling is handled entirley and seperate
	}
	
	char wasMoved;
	if(toUndo.promotedTo != ' '){								//A pawn was promoted
		if(endRow == 0){
			wasMoved = 'P';
		}else{
			wasMoved = 'p';
		}
	}else{											//or not promoted
		wasMoved = theBoard[endRow][endColumn].piece->type;
	}
	if(toUndo.capLocation != "  "){								//generation of captured piece
		delete theBoard[capRow][capColumn].piece;
		theBoard[capRow][capColumn].piece = NULL;
		theBoard[capRow][capColumn].generatePiece(toUndo.capType,this);
		theBoard[capRow][capColumn].piece->hasMoved = toUndo.capturedHasMoved;
	}else{
		delete theBoard[endRow][endColumn].piece;
		theBoard[endRow][endColumn].piece = NULL;
	}
	theBoard[startRow][startColumn].generatePiece(wasMoved,this);
	theBoard[startRow][startColumn].piece->hasMoved = toUndo.thisHasMoved;
	if(toUndo.capLocation != "  " && toUndo.capLocation != toUndo.end){
		if(endColumn > startColumn) theBoard[startRow][startColumn].piece->right = 2;
		if(endColumn < startColumn) theBoard[startRow][startColumn].piece->left = 2;
	}
}
