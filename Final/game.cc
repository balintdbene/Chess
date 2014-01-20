#include"game.h"
#include<iostream>
#include<fstream>
#include<string>
#include"human.h"
#include"difficulty1.h"
#include"difficulty2.h"
#include"difficulty3.h"
#include"difficulty4.h"
#include"window.h"

using namespace std;

string convertPos(const string& pos){
	string index = "  ";
	index[0] = 8 - (pos[1] - 48);
	index[1] = pos[0] - 97;
	return index;
}

Game::Game(): scoreA(0), scoreB(0),parity(0),playerA(NULL), playerB(NULL), validSetup(false), xwptr(new Xwindow()){	//constructor for Game
	//Players are defined after game is called in cmdInterpreter
	//So that they are defined as the correct sub-class
	tdptr = new TextDisplay();
	chessboard = new Board(tdptr);
	usleep(10000);
	DrawBoard();
	DecBoard();
}

Game::~Game(){						//Destructor for Game
		delete playerA;
		playerA = NULL;
		delete playerB;
		playerB = NULL;
		delete chessboard;
		chessboard = NULL;
		delete tdptr;
		tdptr = NULL;
		delete xwptr;
		xwptr = NULL;
}

string determineTeam(char toCheck){//Must be given a valid piece type
	if(toCheck > 96){
		return "Black";
	}else{
		return "White";
	}
}

bool validType(char toCheck){				//Checks for valid piece types
	char validTypes[12] = {'b','k','n','p','q','r','B','K','N','P','Q','R'};
	for(int i = 0; i < 12; i++){
		if(toCheck == validTypes[i]){
			return true;
		}
	}
	return false;
}

void Game::clearBoard(){				//Clears all the visuals of the board
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			delete chessboard->theBoard[i][j].piece;
			chessboard->theBoard[i][j].piece = NULL;
			chessboard->theBoard[i][j].notifyDisplay(*tdptr);
			DrawSq(i,j);
		}
	}
}

void Game::DrawSq(int x, int y){			//Draws a square of the board
	if(x % 2 == 0){													//if row is even
		if(y % 2 == 0) xwptr->fillRectangle((500 + x*500)/9, y*500/9, 500/9, 500/9, Xwindow::Orange);			//if column is even
		if(y % 2 == 1) xwptr->fillRectangle((500 + x*500)/9, y*500/9, 500/9, 500/9, Xwindow::Red);			//if column is odd
	}else if(x % 2 == 1){												//if row is odd
		if(y % 2 == 0) xwptr->fillRectangle((500 + x*500)/9, y*500/9, 500/9, 500/9, Xwindow::Red);			//if column is even
                if(y % 2 == 1) xwptr->fillRectangle((500 + x*500)/9, y*500/9, 500/9, 500/9, Xwindow::Orange);			//if column is odd
	}
}

void Game::DrawPc(int x, int y, char c){		//Draws a piece for the board
	string s = " ";
	s[0] = c;
	if(65 <= s[0] && s[0] <= 90) xwptr->drawString((750+x*500)/9, (250+y*500)/9, s, Xwindow::White);		//draws a white piece
	else xwptr->drawString((750+x*500)/9, (250+y*500)/9, s);							//draws a black piece
}

void Game::ShowCastle(int col, int row, bool doing){								//updates Xwindow and TxtDisplay
	if(doing){												//doing a castle
		if(col == 2){												//queen's side
			DrawSq(col - 2, row);
			DrawPc(col + 1, row, chessboard->theBoard[row][col + 1].piece->type);
			chessboard->theBoard[row][col + 1].notifyDisplay(*tdptr);
			chessboard->theBoard[row][col - 2].notifyDisplay(*tdptr);
		}else if(col == 6){											//king's side
			DrawSq(col + 1, row);
			DrawPc(col - 1, row, chessboard->theBoard[row][col - 1].piece->type);
			chessboard->theBoard[row][col - 1].notifyDisplay(*tdptr);
			chessboard->theBoard[row][col + 1].notifyDisplay(*tdptr);
		}
	}else{													//undoing a castle
		if(col == 2){												//queen's side
			DrawSq(col + 1, row);
			DrawPc(col - 2, row, chessboard->theBoard[row][col - 2].piece->type);
			chessboard->theBoard[row][col + 1].notifyDisplay(*tdptr);
			chessboard->theBoard[row][col - 2].notifyDisplay(*tdptr);
		}else if(col == 6){												//king's side
			DrawSq(col - 1, row);
			DrawPc(col + 1, row, chessboard->theBoard[row][col + 1].piece->type);
			chessboard->theBoard[row][col - 1].notifyDisplay(*tdptr);
			chessboard->theBoard[row][col + 1].notifyDisplay(*tdptr);
		}
	}
}

void Game::DrawBoard(){			//Draws an entire board including pieces
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			DrawSq(j, i);
			if(chessboard->theBoard[i][j].piece != NULL){
				char c = chessboard->theBoard[i][j].piece->type;
				DrawPc(j, i, c);
			}
		}
	}
}

void Game::DecBoard(){			//Draws the coordinates around the board
	for(int i = 0; i < 8; i++){
		string left = "8";
		string bott = "A";
		left[0] -= i;
		bott[0] += i;
		xwptr->drawString(250/9, (250+i*500)/9, left);
		xwptr->drawString((750 + i*500)/9, 500 - 250/9, bott);
	}
}

bool Game::checkSetup(){		//Checks for valid setup
	bool black = false;
	bool white = false;
	for(int i = 0; i < 8; i++){								//checks to see no pawns are on the end rows
		char topP = ' ';
		char botP = ' ';
		if(chessboard->theBoard[0][i].piece != NULL)
			topP = chessboard->theBoard[0][i].piece->type;
		if(chessboard->theBoard[7][i].piece != NULL)
			botP = chessboard->theBoard[7][i].piece->type;
		if(topP == 'p' || topP == 'P' || botP == 'p' || botP == 'P') return false;
	}
	chessboard->setAttacks();								//checks to see if a king is in check and it is
	string wStat = chessboard->gameStatus("White");						//not his turn
	if(parity % 2 == 1 && (wStat == "check" || wStat == "checkmate")) return false;
	string bStat = chessboard->gameStatus("Black");
	if(parity % 2 == 0 && (bStat == "check" || bStat == "checkmate")) return false;
	for(int i = 0; i < 8 && !(black && white); i++){					//checks to see if a king exists for both teams
		for(int j = 0; j < 8 && !(black && white); j++){
			if(chessboard->theBoard[i][j].piece == NULL) continue;
			if(chessboard->theBoard[i][j].piece->type == 'K') white = true;
			if(chessboard->theBoard[i][j].piece->type == 'k') black = true;
		}
	}
	return black && white;
}

void Game::setupMove(int row, int col, char type){						//converts a coordinate
	if(type == 'P' && row != 6) chessboard->theBoard[row][col].piece->hasMoved = true;
	if(type == 'p' && row != 1) chessboard->theBoard[row][col].piece->hasMoved = true;
	if(type == 'r' && !(row == 0 && (col == 0 || col == 7))) chessboard->theBoard[row][col].piece->hasMoved = true;
	if(type == 'R' && !(row == 7 && (col == 0 || col == 7))) chessboard->theBoard[row][col].piece->hasMoved = true;
}

void Game::setupMode(){										//allows a user to setup the board
	cout << "The valid commands are: +, -, =, default, open, done." << endl;
	string command;
	string whiteOptions[5] = {"white","White","w","W","WHITE"};
	string blackOptions[5] = {"black","Black","b","B","BLACK"};
	istream* in = &cin;
	cout << *tdptr;
	while(*in >> command){
		if(command == "+"){								//adding pieces to a board
			char type;
			string location;
			*in >> type;//Done validType function
			*in >> location;//Done validLocation function
			if(!(chessboard->validLocation(location))) continue;
			if(!validType(type)){
				cout << "Sorry that's not a valid type of piece!" << endl;
				continue;
			}
			if(!chessboard->validLocation(location)){
				cout << "That's not a valid square on the chessboard!" << endl;
				break;
			}
			int row = 8-(location[1]-48);
			int column = location[0]-97;
			DrawSq(column, row);
			DrawPc(column, row, type);
			string team = determineTeam(type);
			if(chessboard->theBoard[row][column].piece != NULL){
				delete chessboard->theBoard[row][column].piece;//delete the current piece
				chessboard->theBoard[row][column].piece = NULL;
			}
			chessboard->theBoard[row][column].generatePiece(type,chessboard);//make new piece
			setupMove(row, column, type);
			chessboard->theBoard[row][column].notifyDisplay(*tdptr);//update display
			if(in == &cin)
				printDisplay();
		}else if(command == "-"){									//removing pieces from the board
			string location;
			*in >> location;
			//Check valid input
			if(!(chessboard->validLocation(location))) continue;
			int row = 8-(location[1]-48);
			int column = location[0] -97;
			DrawSq(column, row);
			if(chessboard->theBoard[row][column].piece != NULL){
				delete chessboard->theBoard[row][column].piece;//delete the piece
				chessboard->theBoard[row][column].piece = NULL;
				chessboard->theBoard[row][column].notifyDisplay(*tdptr);//update display
			if(in == &cin)
				printDisplay();
			}
			
		}else if(command == "="){									//change the turn
			string whosTurn;
			*in >> whosTurn;
			//There are five different versions of each white and black
			for(int i = 0; i < 5;i++){
				if(whosTurn == whiteOptions[i]){
					if(in == &cin)
						cout << "White to move" << endl;
					parity = 0;
					break;
				}
				if(whosTurn == blackOptions[i]){
					if(in == &cin)
						cout <<"Black to move" << endl;
					parity = 1;
					break;
				}
			}
		}else if(command == "default"){									//sets up the board with a default setup
			clearBoard();
			chessboard->setup();
			DrawBoard();
			parity = 0;
			if(in == &cin)
				cout << *tdptr;
		}else if(command == "done"){									//exists setup mode if valid setup
			//check all conditions
			if(in != &cin){
				printDisplay();
				if(parity % 2 == 0)
					cout << "White to move" << endl;
				else if(parity % 2 == 1)
					cout << "Black to move" << endl;
				delete in;
			}
			validSetup = true;
			if(checkSetup()){
				cout << "Setup mode completed" << endl; //or "Missing condition, fix it before you can leave
				return;
			}else
				cout << "That is not a valid setup for the board, please fix it." << endl;
		}else if(command == "open"){		//wipes current board, opens a saved game, valid input states that the file ends with "done", 
			clearBoard();			//as well as the fact that it will never open a new file from the file. Maybe also have legit setup interms of kings
			string file;
			*in >> file;
			in = new ifstream(file.c_str());
		}else{
			cout << "Invalid command" << endl;
		}
	}
}

void Game::printScore(){				//prints the amount of games won for each player
	cout << "Final Score:" << endl;
	if(scoreA % 2 == 0)
		cout << "White: " << scoreA / 2 << endl;
	else
		cout << "White: " << scoreA / 2.0 << endl;
	if(scoreB % 2 == 0)
		cout << "Black: " << scoreB / 2 << endl;
	else
		cout << "Black: " << scoreB / 2.0 << endl;
}

void Game::printDisplay(){				//prints the text display
	cout << *tdptr;
}

bool Game::validPlayer(string name, bool isPlayerA){	//checks if the input for players is valid
	string validNames[5] = {"human","computer[1]","computer[2]","computer[3]","computer[4]"};
	for(int i =0; i < 5; i++){
		if(name == validNames[i]){
			//Along with returning true, define PlayerA/B as the correct class
			if(isPlayerA){
				switch(i){
					case 0: 
						playerA = new Human(chessboard, "White");
						break;
					case 1:
						playerA = new Difficulty1(chessboard, "White");
						break;
					case 2:
						playerA = new Difficulty2(chessboard, "White");
						break;
					case 3:
						playerA = new Difficulty3(chessboard, "White");
						break;
					case 4:
						playerA = new Difficulty4(chessboard, "White");
				}
			}else{
				switch(i){
					case 0: 
						playerB = new Human(chessboard, "Black");
						break;
					case 1:
						playerB = new Difficulty1(chessboard, "Black");
						break;
					case 2:
						playerB = new Difficulty2(chessboard, "Black");
						break;
					case 3:
						playerB = new Difficulty3(chessboard, "Black");
						break;
					case 4:
						playerB = new Difficulty4(chessboard, "Black");
				}
			}
			return true;
		}
	}
	cout << "Invalid player name: " << name << endl;
	return false;
}

void Game::undo(){		//undoes a move on the stack of previous moves and updates visuals
	Move past = pastMoves.back();
	pastMoves.pop_back();
	pastUndos.push_back(past);
	chessboard->undoMove(past);                                     //undoes the move
	int startRow = 8-(past.start[1] - 48);
	int startColumn = past.start[0] - 97;
	int endRow = 8-(past.end[1] - 48);
	int endColumn = past.end[0] - 97;
	chessboard->theBoard[startRow][startColumn].notifyDisplay(*tdptr);
	DrawSq(startColumn, startRow);
	DrawPc(startColumn, startRow, chessboard->theBoard[startRow][startColumn].piece->type);
	DrawSq(endColumn, endRow);
	chessboard->theBoard[endRow][endColumn].notifyDisplay(*tdptr);
	if(past.capLocation != "  "){
		int capRow = 8-(past.capLocation[1] - 48);
		int capColumn = past.capLocation[0] - 97;
		DrawPc(capColumn, capRow, chessboard->theBoard[capRow][capColumn].piece->type);
		chessboard->theBoard[capRow][capColumn].notifyDisplay(*tdptr);
	}
	if(past.castling) ShowCastle(endColumn, endRow, false);
	parity++;
	printDisplay();
}


void Game::redo(){		//redoes a move on the stack of undone moves and updates visuals
	Move unDone = pastUndos.back();
	pastUndos.pop_back();
	pastMoves.push_back(unDone);
	chessboard->doMove(unDone);
	int startRow = 8-(unDone.start[1] - 48);
	int startColumn = unDone.start[0] - 97;
	int endRow = 8-(unDone.end[1] - 48);
	int endColumn = unDone.end[0] -97;
	chessboard->theBoard[endRow][endColumn].notifyDisplay(*tdptr);
	DrawSq(endColumn, endRow);
	DrawPc(endColumn, endRow, chessboard->theBoard[endRow][endColumn].piece->type);
	DrawSq(startColumn,startRow);
	chessboard->theBoard[startRow][startColumn].notifyDisplay(*tdptr);
	if(unDone.capLocation != "  "){
		int capRow = 8-(unDone.capLocation[1] - 48);
		int capColumn = unDone.capLocation[0]- 97;
		DrawPc(capColumn, capRow, chessboard->theBoard[capRow][capColumn].piece->type);
		chessboard->theBoard[capRow][capColumn].notifyDisplay(*tdptr);
	}
	if(unDone.castling) ShowCastle(endColumn, endRow, true);
	printDisplay();
	parity++;
}

bool Game::statusCheck(){
	string player = parity % 2 == 0 ? "Black" : "White";                    //checks to see whose turn it was
	string status = chessboard->gameStatus(player);                         //checks status of game
	bool inGame= true;
	if(status == "check"){                                                  //outputs any special events to the user
		cout << player << " is in check!" << endl;
	}else if(status == "stalemate"){					//stalemate and checkmate both handle the game ending
		cout << "Stalemate!" << endl << "Game over!" << endl;
		inGame = false;
		validSetup = false;
		delete playerA;
		delete playerB;
		playerA = NULL;
		playerB = NULL;
		scoreA++;
		scoreB++;
		parity = 0;
		pastMoves.clear();
		pastUndos.clear();
	}else if(status == "checkmate"){
		player = parity % 2 == 0 ? "White" : "Black";
		cout << "CheckMate!" << endl << player << " wins!" << endl;
		inGame = false;
		validSetup = false;
		delete playerA;
		delete playerB;
		playerA = NULL;
		playerB = NULL;
		player == "White" ? scoreA += 2 : scoreB += 2;
		parity = 0;
		pastMoves.clear();
		pastUndos.clear();
	}
	return inGame;
}

void Game::cmdInterpreter(){					//takes input from user
	cout << "Valid commands are: setup, game, move, resign, save, undo, redo." << endl;
	string command;
	Move moveToDo;
	bool inGame = false;
	while(cin >> command){
		if(command == "game" && !inGame){			//allows the types of players to be chosen and initializes the game
			inGame = true;
			if(!validSetup){
				clearBoard();
				chessboard->setup();
				DrawBoard();
				parity = 0;
			}
			cin >> command;
			if(validPlayer(command,true)){
				cin >> command;
				if(validPlayer(command,false)){
					printDisplay();
				}
			}else{
				if(playerA != NULL){//If it was B that was invalid reset A					
					delete playerA;
				}
				cout << "Incorrect player name" << endl;
			}
			chessboard->setAttacks();
			parity++;
			inGame = statusCheck();
			parity++;
		}else if(command == "resign" && inGame){
			if(parity % 2 == 0){
				cout << "Black wins!" << endl;
				scoreB += 2;
			}else{
				cout << "White wins!" << endl;
				scoreA += 2;
			}
			validSetup = false;
			inGame = false;
			parity = 0;
			pastMoves.clear();
			pastUndos.clear();
			delete playerA;
			playerA = NULL;
			delete playerB;
			playerB = NULL;
		}else if(command == "move" && inGame){			//allows a player to make a move
			pastUndos.clear();	
			chessboard->setAttacks();
			if(parity % 2 == 0) moveToDo = playerA->getMove();				//gets moved from whichever player whose turn it is
			if(parity % 2 == 1) moveToDo = playerB->getMove();
			pastMoves.push_back(moveToDo);
			chessboard->doMove(moveToDo);							//does the move
			int startRow = 8-(moveToDo.start[1] - 48);
                        int startColumn = moveToDo.start[0] - 97;
                        int endRow = 8-(moveToDo.end[1] - 48);
                        int endColumn = moveToDo.end[0] - 97;
			if(moveToDo.capLocation != "  "){
				int capRow = 8-(moveToDo.capLocation[1] - 48);
				int capColumn = moveToDo.capLocation[0] - 97;
				chessboard->theBoard[capRow][capColumn].notifyDisplay(*tdptr);
				DrawSq(capColumn, capRow);
			}
			chessboard->theBoard[endRow][endColumn].notifyDisplay(*tdptr);			//updates TextDisplay
                        chessboard->theBoard[startRow][startColumn].notifyDisplay(*tdptr);
			DrawSq(startColumn, startRow);							//updates graphics
			DrawSq(endColumn, endRow);
			DrawPc(endColumn, endRow, chessboard->theBoard[endRow][endColumn].piece->type);	
			if(moveToDo.castling) ShowCastle(endColumn, endRow, true);
			printDisplay();
			chessboard->setAttacks();
			inGame = statusCheck();
			parity++;
		}else if(command == "setup" && !inGame){		//allows a user to setup the board
			if(!validSetup) clearBoard();
			setupMode();
		}else if(command == "redo" && inGame && !pastUndos.empty()){	//allows a player to redo an undone move
			redo();
		}else if(command == "undo" && inGame && !pastMoves.empty()){	//allows a player to undo a move
			undo();
		}else if(command == "save" && inGame){					//saves the current game in a file
			string outfile;
			cin >> outfile;
			ofstream out(outfile.c_str());
			for(int i = 0; i < 8; i++){
				for(int j = 0; j < 8; j++){
					if(chessboard->theBoard[i][j].piece == NULL) continue;
					string place = "  ";
					place[0] = j + 97;
					place[1] = (8-i) + 48;
					out << "+" << " " << chessboard->theBoard[i][j].piece->type << " " << place << endl;
				}
			}
			parity % 2 == 0 ? out << "= White" : out << "= Black";
			out << endl << "done";
		}else{
			cout << "Invalid command entered" << endl;
		}
	}
	printScore();
}
