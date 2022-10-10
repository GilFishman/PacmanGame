#ifndef _GHOST_H_
#define _GHOST_H_

#include "Creature.h"
#include <time.h>
class Ghost :public Creature
{
	board b; 

public:
	//ctor
	Ghost() :Creature('$', Right) {};
	//methods
	void move(char curr, char next, bool Setcolor, int height, int width,board& Board, bool isSilent);
	void moveSmartGhost(char curr, char next, bool Setcolor, int height, int width, board& Board, Point PacPos);
	void moveHalfSmartGhost(char curr, char next, bool Setcolor, int height, int width, board& Board, Point PacPos);
	int GetRoute(Point PacmanPos);
	int changeDirSmartGhost(Point PacmanPos);
	//getters and setters
	void setLocation(int i)
	{
		Point body0;
		body0.setX(b.getGhostPos(0, i));
		body0.setY(b.getGhostPos(1, i));
		setPos(0, body0);
		setPos(1, body0);
	}
};

#endif