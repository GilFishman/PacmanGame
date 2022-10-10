#include "Pacman.h"
/*init the chosen direction according to user choice*/
const int Pacman::getDirection(char key)
{
	for (int i = 0; i < 10; i++)
	{
		if (key == arrowkeys[i])
			return i;
	}
	return -1;
}

void Pacman::move(bool Setcolor, char PacPos, int height, int width, bool isSilent)
{
	/*if the pacman hits a wall it stops and waiting to a new direction*/
	if (PacPos == (char)178)
		setBody(1, 0);
	/*the pacman eats the food*/
	else
	{
		if (isSilent==false)
			getBody(0).draw(' ');
		setBody(0, 1);
	}
	Point body1;
	body1.setX(getXbody(1));
	body1.setY(getYbody(1));
	body1.move(getDir(), height, width);
	setPos(1, body1);
	if (Setcolor == true)
		setTextColor(getColor());
	if (isSilent==false)
		getBody(0).draw('@');
}


