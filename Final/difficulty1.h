#ifndef __DIFFICULTY1_H__
#define __DIFFICULTY1_H__

#include"move.h"
#include"player.h"

class Difficulty1: public Player{
	public:
	Difficulty1(Board*, const string&);
	Move getMove();
};

#endif
