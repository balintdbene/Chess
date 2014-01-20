#include"textdisplay.h"
#include<iostream>

using std::string;

using std::ostream;
using std::endl;
using std::cerr;
TextDisplay::TextDisplay(){
	//Allocate memory for an 10x10 array to output the board and row/line info
	theDisplay = new char*[10];
	for(int i = 0; i < 10; i++){
		theDisplay[i] = new char[10];
	}
	//Initialize '_''s and ' ''s
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			if(i%2 == 0){
				if(j%2 == 0){
					theDisplay[i][j] = ' ';
					//notify(i, j, ' ');
				}else{
					theDisplay[i][j] = '_';
					//notify(i, j, '_');
				}
			}else{
				if(j%2==0){
					theDisplay[i][j] = '_';
					//notify(i, j, '_');
				}else{
					theDisplay[i][j] = ' ';
					//notify(i, j, ' ');
				}
			}
		}
	}
	//Initialize bottom two rows
	for(int j = 0; j < 10; j++){
		theDisplay[8][j] = ' ';//Second last row is blank
		theDisplay[9][j] = j+95;//Last column letters (aligned below columns)
	}
	//Initialize left two columns
	for(int i =0; i < 10; i++){
		theDisplay[i][0] = 8-i+48;//8-i is the row number, an int [0-9] + 48 is the char code for that int
		theDisplay[i][1] = ' ';//Blank space before actual board 
	}
	theDisplay[8][0] = ' ';
	theDisplay[9][0] = ' ';//Bottom left is blank not ':'

//	std::cerr << "TextDisplay Contrcutor end" << std::endl;
}

TextDisplay::~TextDisplay(){		//destructor for textdisplay
	for(int i = 0; i < 10; i++){
		delete [] theDisplay[i];
	}
	delete [] theDisplay;
}

void TextDisplay::notify(int r, int c, char symbol){	//updates condition of the representation of a chessboard square
	theDisplay[r][c+2] = symbol;	//compensates for location of square
}

ostream& operator<<(ostream& out, const TextDisplay& td){	//output overload for the text display
	for(int i = 0; i < 10; i++){
		for(int j =0; j < 10; j++){
			out << td.theDisplay[i][j];
		}
		out << endl;
	}
	return out;
}


