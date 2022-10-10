#ifndef _CREATURE_H_
#define _CREATURE_H_

#include "Point.h"
#include "board.h"

class Creature
{
	char figure;
	int direction;
	Point body[2];
	int color;
public:
	Creature(char _figure, int _dir):figure(_figure),direction(_dir) {};
	//Setters
	void setFigure(const char c)
	{
		figure = c;
	}
	void setColor(int c)
	{
		color = c;
	}
	void setDirection(int dir)
	{
		direction = dir;
	}
	void SetYbody1(int y)
	{
		body[1].setY(y);
	}
	void SetXbody1(int x)
	{
		body[1].setX(x);
	}
	void SetYbody0(int y)
	{
		body[0].setY(y);
	}
	void SetXbody0(int x)
	{
		body[0].setX(x);
	}
	void setBody(int i, int j)
	{
		body[i] = body[j]; 
	}
	void setPos(int i, Point p)
	{
		body[i].setX(p.getX());
		body[i].setY(p.getY());
	}
	//Getters
	const int getDir()
	{
		return direction;
	}
	const int getColor()
	{
		return color; 
	}
	const int getXbody(int i)
	{
		return body[i].getX();
	}
	const int getYbody(int i)
	{
		return body[i].getY();
	}
	Point getBody(int i)
	{
		return body[i];
	}

	void SilentMove(int dir, int height, int width)
	{	
		setBody(0, 1);
		Point body1;
		body1.setX(getXbody(1));
		body1.setY(getYbody(1));
		body1.move(dir, height, width);
		setPos(1, body1);
	};
};

#endif