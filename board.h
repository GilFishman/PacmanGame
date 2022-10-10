#ifndef _BOARD_H_
#define _BOARD_H_
#include "io_utils.h"
using namespace std;
#include "Point.h"
#include <time.h>

class board 
{
	enum {WIDTH=80, HEIGHT=24};
	char Board[HEIGHT][WIDTH]; 

	int RealHeight; 
	int RealWidth; 
	int num_of_ghost=0; 
	int num_of_bread=0; 
	int XPacPos;
	int YPacPos;
	int XlegendPos;
	int YlegendPos;
	int GhostPos[2][4]; 
	bool validfile=true;
	bool isPacman = false; 
	bool isLegend = false; 
	
public:
	//methods
	void buildboard(string& playerchoice);
	void ReadChar(char c, int & i, int & j, int& countchar);
	void initLegend();
	void printboard(bool Setcolor, string& playerchoice);
	void updatePos(int x, int y)
	{
		Board[y][x] = ' ';
	};
	void SetPos(int x, int y,char c)
	{
		Board[y][x] = c;
	};
	void CountFood();

	//getters and setters
	const char getSymbol(int x, int y)
	{
		return Board[y][x];
	};
	const int getXpac()
	{
		return XPacPos;
	}
	const int getYpac()
	{
		return YPacPos;
	}
	const int getGhostPos(int i, int j)
	{
		return GhostPos[i][j];
	}
	const int getNumOfGhost()
	{
		return num_of_ghost;
	}
	const int getNumOfFood()
	{
		return num_of_bread;
	}
	const int getRealHeight()
	{
		return RealHeight;
	}
	const int getRealWidth()
	{
		return RealWidth;
	}
	void setNumOfGhost()
	{
		num_of_ghost = 0; 
	}
	void setFood()
	{
		num_of_bread = 0; 
	}
	const bool getValid()
	{
		return validfile; 
	}

};
#endif 
