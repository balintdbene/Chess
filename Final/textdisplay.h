#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__

#include<iostream>
#include<string>

class TextDisplay{
	char**theDisplay;
	public:
	TextDisplay();
	~TextDisplay();
	void notify(int, int, char);

	friend std::ostream& operator<<(std::ostream& out, const TextDisplay& td);
};

#endif
