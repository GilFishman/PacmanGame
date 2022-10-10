#ifndef _POINT_H_
#define _POINT_H_

#include "io_utils.h"
using namespace std;

enum
{
	up = 0,
	UP=1, 
	down=2,
	DOWN=3, 
	Left=4,
	LEFT=5,
	Right=6,
	RIGHT=7,
	Stop=8,
	STOP=9
};
class Point 
 {
	int x, y;
public:
	//methods 
	void draw(char ch);
	void move(int direction, int Height, int Width);
	//setters and getters
	const int getX()
	{
		return x;
	}
	const int getY()
	{
		return y;
	}
	void setY(int a)
	{
		y = a; 
	}
	void setX(int a)
	{
		x = a; 
	}
};


#endif
