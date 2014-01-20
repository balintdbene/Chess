#ifndef __DIFFICULTY4_H__
#define __DIFFICULTY4_H__

#include"player.h"
#include"move.h"

class Difficulty4: public Player{
	public:
	Difficulty4(Board*, const string&);
	Move getMove();
};

#endif
