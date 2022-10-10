#ifndef _PACMAN_H_
#define _PACMAN_H_

#include "Creature.h"

class Pacman:public Creature
{
	char arrowkeys[10]; 

public:
	//ctor
	Pacman() :Creature('@', STOP) {};
	//methods
	void move(bool Setcolor, char PacPos, int height, int width, bool isSilent);
	//getters and setters
	const int getDirection(char key);
	void setArrowKeys(const char* keys)
	{ // "wWxXaAdDsS
		arrowkeys[0] = keys[0];
		arrowkeys[1] = keys[1];
		arrowkeys[2] = keys[2];
		arrowkeys[3] = keys[3];
		arrowkeys[4] = keys[4]; 
		arrowkeys[5] = keys[5];
		arrowkeys[6] = keys[6];
		arrowkeys[7] = keys[7];
		arrowkeys[8] = keys[8];
		arrowkeys[9] = keys[9];
	}
};

#endif 
