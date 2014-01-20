#ifndef __DIFFICULTY2_H__
#define __DIFFICULTY2_H__

#include"move.h"
#include"player.h"


class Difficulty2: public Player{
	public:
	Difficulty2(Board*, const string&);
	Move getMove();
};

#endif
