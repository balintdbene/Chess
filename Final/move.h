#ifndef __MOVE_H__
#define __MOVE_H__
#include<string>

using std::string;

struct Move{
	Move();
	string start;
	string end;
	string capLocation;
	char capType;
	char promotedTo;
	bool thisHasMoved;
	bool capturedHasMoved;
	bool castling;
	bool operator==(const Move& other);
	Move& operator=(const Move& other);
};

#endif
