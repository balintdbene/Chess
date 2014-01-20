#include"move.h"
Move::Move(){			//constructor for move
	start = "  ";
	end = "  ";
	capLocation = "  ";
	capType = ' ';
	promotedTo = ' ';
	thisHasMoved = false;
	capturedHasMoved = false;
	castling = false;
}
bool Move::operator==(const Move& other){	//equality overload
	
	bool startSame = other.start == start;
	bool endSame = other.end == end;
	bool capTypeSame = other.capType == capType;
	bool capLocationSame = other.capLocation == capLocation;
	bool promotedToSame = other.promotedTo == promotedTo;
	bool hasMovedSame = other.thisHasMoved == thisHasMoved && other.capturedHasMoved == capturedHasMoved;
	bool castlingSame = other.castling == castling;
	return startSame && endSame && capTypeSame && capLocationSame && promotedToSame && hasMovedSame && castlingSame;
}

Move& Move::operator=(const Move& other){	//assignment overload
	start = other.start;
	end = other.end;
	capLocation = other.capLocation;
	capType = other.capType;
	promotedTo = other.promotedTo;
	thisHasMoved = other.thisHasMoved;
	capturedHasMoved = other.capturedHasMoved;
	castling = other.castling;
}
