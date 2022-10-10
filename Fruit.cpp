#include "Fruit.h"

void Fruit::move(char curr, char next, bool Setcolor, int height,int width, board& Board, bool isSilent)
{
	srand(time(NULL));
	/*if the fruit hits a wall it changes the direction*/
	if (next == (char)178)
	{
		setBody(1, 0);
		setDirection(rand() % 7);
		Point body1;
		body1.setX(getXbody(1));
		body1.setY(getYbody(1));
		body1.move(getDir(),height,width);
		setPos(1, body1);
		if (Setcolor == true)
			setTextColor(GREEN);
		if (isSilent == false)
			getBody(0).draw(getValue());
	}
	else 
	{
		if (Setcolor == true)
			setTextColor(BLUE);
		if (isSilent == false)
			getBody(0).draw(curr);
		setBody(0, 1);
		Point body1;
		body1.setX(getXbody(1));
		body1.setY(getYbody(1));
		body1.move(getDir(), height, width);
		setPos(1, body1);
		if (Setcolor == true)
			setTextColor(getColor());
		if (isSilent == false)
			getBody(0).draw(getValue());
	}
}