#include"human.h"
#include"move.h"
#include<iostream>
#include<string>
#include<vector>

using std::string;
using std::cin;
using std::cout;
using std::endl;

Human::~Human(){};	//not responsible for calling any other objects destructors

Human::Human(Board* chessboard, const string& team){	//constructor for Human
	this->chessboard = chessboard;
	this->team = team;
}

bool validPromotion(char toCheck,string team){		//checks for valid promotion type
	if(team == "White"){
		return toCheck == 'Q' || toCheck == 'N' || toCheck == 'R' || toCheck == 'B';
	}else{
		return toCheck == 'q' || toCheck == 'n' || toCheck == 'r' || toCheck == 'b';	
	}
}

Move Human::getMove(){		//returns a valid move from a Human player
	string start;
	string end;
	while(true){
		Move attempt;
		attempt.capLocation = "  ";//This is changed to end if necessary, en passent will need to be done seperately somehow
		attempt.capType = ' ';//Same as above
		attempt.promotedTo = ' ';//^^^^^^^^^^

		cout << "Enter your start and end positions:" << endl;
		cin >> start;
		cin >> end;

		if(!chessboard->validLocation(start)){				//I feel like this one should go to the board and check if there is a movable piece at the location
			cout << "You can't start from there" << endl;
			continue;
		}

		if(!chessboard->validLocation(end)){				//this one should be different from the one above, we need king and some other
			cout << "You can't end there" << endl;			//pieces because this doesnt even make sense yet, need to check for checks and stuff
			continue;
		}

		int startRow =8-(start[1]-48);
		int startColumn = start[0]-97;
		int endRow = 8-(end[1]-48);
		int endColumn = end[0]-97;

		//DEFINE A TEMP PIECE JUST SO IT'S SHORTER!!!!
		Piece* pieceToMove = chessboard->theBoard[startRow][startColumn].piece;
		//Must be a piece at the start location
		if(pieceToMove == NULL){
			cout << "Sorry that's not a valid move, there's no piece at " << start << endl;
			continue;//Moves back to start of while
		}
		
		//Must be your own piece at the start location
		if(pieceToMove->team != team){
			cout << "That's not your piece!!!" << endl;
			continue;
		}
				
		//End location must be blank or another players piece
		if(chessboard->theBoard[endRow][endColumn].piece != NULL){
			if(chessboard->theBoard[endRow][endColumn].piece->team == team){
				cout << "You can't attack your own piece!" << endl;
				continue;
			}else{
				attempt.capLocation = end;
				attempt.capType = chessboard->theBoard[endRow][endColumn].piece->type;
				attempt.capturedHasMoved = chessboard->theBoard[endRow][endColumn].piece->hasMoved;
			}
		}
		
		//PAWN PROMOTION
		if(team == "White"){
			if(endRow == 0){
				if(pieceToMove->type == 'P'){
					char promotion;
					cin >> promotion;
					if(validPromotion(promotion,team)){
						attempt.promotedTo = promotion;
					}else{
						cout << "Invalid piece for promotion" << endl;
						continue;
					}
				}
			}
		}else{//Team is Black
			if(endRow == 7){
				if(pieceToMove->type == 'p'){
					char promotion;
					cin >> promotion;
					if(validPromotion(promotion,team)){
						attempt.promotedTo = promotion;
					}else{
						cout << "Invalid piece for promotion" << endl;
						continue;
					}
				}
			}
		}
		
		//CASTLING
		if(team == "White" && start == "e1" && pieceToMove->type == 'K'){
			if(end == "g1" || end == "c1"){
				attempt.castling = true;
			}
		}
		if(team == "Black" && start == "e8" && pieceToMove->type == 'k'){
			if(end == "g8" || end == "c8"){
				attempt.castling = true;
			}
		}
		attempt.start = start;
		attempt.end = end;
		attempt.thisHasMoved = pieceToMove->hasMoved;
		if(chessboard->theBoard[endRow][endColumn].piece != NULL){
			attempt.capType = chessboard->theBoard[endRow][endColumn].piece->type;
			attempt.capLocation = end;
		}
				
		vector<Move> checkAgainst = pieceToMove->getValidMoves(start,false);
		
		//EN PASSANT
		
		string encap = "  ";
		encap[1] = start[1];
		Piece* pc = chessboard->theBoard[startRow][startColumn].piece;
		if((pc->type == 'p' || pc->type == 'P') && (pc->left == 1 || pc->right == 1)){
			if(team == "White") attempt.capType = 'p';
			else attempt.capType = 'P';
			if(pc->left == 1)
				encap[0] = start[0] - 1;
			if(pc->right == 1)
				encap[0] = start[0] + 1;
			attempt.capLocation = encap;
		}
		for(vector<Move>::iterator i = checkAgainst.begin(); i != checkAgainst.end(); i++){
/* For testing purposes
		cout << endl << "NEW ONE" << endl;
			cout << "attempt: " << attempt.start << " " << i->start << endl;
			cout << "attempt: " << attempt.end << " " << i->end << endl;
			cout << "attempt: " << attempt.capLocation << " " << "*" << i->capLocation << "*" << endl;
			cout << "attempt: " << attempt.capType << " " << i->capType << endl;
			cout << "attempt: " << attempt.promotedTo << " " << i->promotedTo << endl;
			cout << "attempt: " << attempt.thisHasMoved << " " << i->thisHasMoved << endl;
			cout << "attempt: " << attempt.capturedHasMoved << " " << i->capturedHasMoved << endl;
			cout << "attampt: " << attempt.castling << " " << i->castling << endl;*/
		if(attempt == *i){
			pieceToMove->hasMoved = true;
			return attempt;
			}
		}
		cout << "Sorry that move isn't valid try again!!" << endl;	
	}
}
