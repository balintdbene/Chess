#ifndef __DIFFICULTY3_H__
#define __DIFFICULTY3_H__

#include"move.h"
#include"player.h"

class Difficulty3: public Player{
	public:
	Difficulty3(Board*, const  string&);
	Move getMove();
};

#endif
