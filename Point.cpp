#include "Point.h"

void Point::draw(char ch)
{
	gotoxy(x, y);
	cout << ch << endl;
}

void Point::move(int direction, int Height, int Width)
{
	switch (direction)
	{
	case up: 
		--y;
		if (y < 0) 
		{
			y = Height - 1;
		}
		break;
	case UP: 
		--y;
		if (y < 0)
		{
			y = Height - 1;
		}
		break;
	case down: 
		++y;
		if (y > Height - 1)
		{
			y = 0;
		}
		break;
	case DOWN: 
		++y;
		if (y > Height - 1)
		{
			y = 0;
		}
		break;
	case Left: 
		--x;
		if (x < 0) 
		{
			x = Width - 1;
		}
		break;
	case LEFT: 
		--x;
		if (x < 0)
		{
			x = Width - 1;
		}
		break;
	case Right: 
		++x;
		if (x > Width - 1)
		{
			x = 0;
		}
		break;
	case RIGHT:
		++x;
		if (x > Width - 1)
		{
			x = 0;
		}
		break;
	case Stop: 
		break;
	case STOP:
		break; 
	}
}

