#include "Ghost.h"

void Ghost::move(char curr,char next,bool Setcolor,int height,int width,board& Board,bool isSilent)
{
	srand(time(NULL));
	/*if the ghost hits a wall it changes the direction*/
	if (next == (char)178)
	{
		setBody(1, 0);
		setDirection(rand() % 7);
		Point body1;
		body1.setX(getXbody(1));
		body1.setY(getYbody(1));
		body1.move(getDir(),height, width);
		setPos(1, body1);
		if (Setcolor == true)
			setTextColor(RED);
		if (isSilent == false)
			getBody(0).draw('&');
	}
	/*ghost dont eat food*/
	else if (curr=='*')
	{
		if (Setcolor == true)
			setTextColor(BLUE);
		if (isSilent == false)
			getBody(0).draw('*');
		setBody(0, 1);
		Point body1;
		body1.setX(getXbody(1));
		body1.setY(getYbody(1));
		body1.move(getDir(), height, width);
		setPos(1, body1);
		if (Setcolor == true)
			setTextColor(getColor());
		if (isSilent == false)
			getBody(0).draw('&');
	}
	else
	{
		if (isSilent == false)
			getBody(0).draw(' ');
		setBody(0, 1);
		Point body1;
		body1.setX(getXbody(1));
		body1.setY(getYbody(1));
		body1.move(getDir(), height, width);
		setPos(1, body1);
		if (Setcolor == true)
			setTextColor(getColor());
		if (isSilent == false)
			getBody(0).draw('&');
	}
}

void Ghost::moveSmartGhost(char curr, char next, bool Setcolor, int height, int width, board& Board,Point PacPos)
{
	/*if the ghost hits a wall it changes the direction*/
	if (next == (char)178)
	{
		setBody(1, 0);
		setDirection(changeDirSmartGhost(PacPos));
		Point body1;
		body1.setX(getXbody(1));
		body1.setY(getYbody(1));
		body1.move(getDir(), height, width);
		setPos(1, body1);
		if (Setcolor == true)
			setTextColor(RED);
		getBody(0).draw('&');
	}
	/*ghost dont eat food*/
	else if (curr == '*')
	{
		if (Setcolor == true)
			setTextColor(BLUE);
		getBody(0).draw('*');
		setBody(0, 1);
		Point body1;
		body1.setX(getXbody(1));
		body1.setY(getYbody(1));
		body1.move(GetRoute(PacPos), height, width);
		setPos(1, body1);
		if (Setcolor == true)
			setTextColor(getColor());
		getBody(0).draw('&');
	}
	else
	{
		getBody(0).draw(' ');
		setBody(0, 1);
		Point body1;
		body1.setX(getXbody(1));
		body1.setY(getYbody(1));
		body1.move(GetRoute(PacPos), height, width);
		setPos(1, body1);
		if (Setcolor == true)
			setTextColor(getColor());
		getBody(0).draw('&');
	}
}

int Ghost::GetRoute(Point PacmanPos)
{
	int dirx, diry, direction;
	dirx = abs(getXbody(0) - PacmanPos.getX());
	diry = abs(getYbody(0) - PacmanPos.getY());
	if (dirx < diry)
	{
		if (getYbody(0) < PacmanPos.getY())
		{
			direction = DOWN; 
		}
		else
		{
			direction = UP; 
		}
	}
	else
	{
		if (getXbody(0) < PacmanPos.getX())
		{
			direction = RIGHT;
		}
		else
		{
			direction = LEFT;
		}
	}
	return direction; 
}

int Ghost::changeDirSmartGhost(Point PacmanPos)
{ 
	if (getDir() == RIGHT || getDir() == LEFT) 
	{
		if (getYbody(0) < PacmanPos.getY())
		{
			return DOWN;
		}
		else
		{
			return UP;
		}
	}
	if (getDir() == UP || getDir() == DOWN)
	{
		if (getXbody(0) < PacmanPos.getX())
		{
			return RIGHT;
		}
		else
		{
			return LEFT;
		}
	}
}

void Ghost::moveHalfSmartGhost(char curr, char next, bool Setcolor, int height, int width, board& Board, Point PacPos)
{
	srand(time(NULL));
	
	/*if the ghost hits a wall it changes the direction*/
	if (next == (char)178)
	{
		setBody(1, 0);
		setDirection(changeDirSmartGhost(PacPos));
		Point body1;
		body1.setX(getXbody(1));
		body1.setY(getYbody(1));
		body1.move(getDir(), height, width);
		setPos(1, body1);
		if (Setcolor == true)
			setTextColor(RED);
		getBody(0).draw('&');
	}
	/*ghost dont eat food*/
	else if (curr == '*')
	{
		if (Setcolor == true)
			setTextColor(BLUE);
		getBody(0).draw('*');
		setBody(0, 1);
		Point body1;
		body1.setX(getXbody(1));
		body1.setY(getYbody(1));
		body1.move(GetRoute(PacPos), height, width);
		setPos(1, body1);
		if (Setcolor == true)
			setTextColor(getColor());
		getBody(0).draw('&');
	}
	else
	{
		getBody(0).draw(' ');
		setBody(0, 1);
		Point body1;
		body1.setX(getXbody(1));
		body1.setY(getYbody(1));
		body1.move(GetRoute(PacPos), height, width);
		setPos(1, body1);
		if (Setcolor == true)
			setTextColor(getColor());
		getBody(0).draw('&');
	}
}