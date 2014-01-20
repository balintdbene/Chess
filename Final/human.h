#ifndef __HUMAN_H__
#define __HUMAN_H__

#include"move.h"
#include"player.h"

class Human: public Player{
	public:
	Human(Board*, const string&);
	Move getMove();				//returns a valid move from the Human
	~Human();
};

#endif
