#ifndef __GAME_H__
#define __GAME_H__

#include<unistd.h>
#include"player.h"
#include"board.h"
#include"textdisplay.h"

class Game{
	int scoreA;
	int scoreB;
	Player* playerA;
	Player* playerB;
	Board* chessboard;
	TextDisplay* tdptr;
	Xwindow* xwptr;
	int parity;					//keeps track of whose turn it is
	bool validSetup;
	vector<Move> pastMoves;
	vector<Move> pastUndos;
	public:
	Game();
	~Game();
	void cmdInterpreter();				//takes general input from the user
	
	private:
	void printScore();
	void printDisplay();
	bool validPlayer(string name,bool isPlayerA);

	void redo();
	void undo();
	bool statusCheck();				//checks for check, checkmate, stalemate

	void clearBoard();
	void setupMode();				//allows users to set up a board
	bool checkSetup();

	void setupMove(int, int, char);			//visuals related methods
	void DrawSq(int x, int y);
	void DrawPc(int x, int y, char c);
	void DrawBoard();
	void DecBoard();
	void ShowCastle(int, int, bool);
};

std::string convertPos(const std::string&);

#endif
