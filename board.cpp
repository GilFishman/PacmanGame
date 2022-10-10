#include "board.h"
#include <iostream>
#include <fstream>

/*the function init the game board*/
void board::buildboard(string& playerchoice)
{
	num_of_ghost = 0; 
	validfile = true; 
	isPacman = false;
	isLegend = false;
	int col = 0;
	int row = 0; 
	char c; 
	int countchars = 0; 
	ifstream infile;
	infile.open(playerchoice, ios::ate);
	if (!infile)
	{
		validfile = false; 
	}
	else
	{
		int filesize = infile.tellg(); 
		if (filesize == 0)
		{
			validfile = false;
		}
		infile.seekg(0, infile.beg); 
		while (row <= HEIGHT && col <= WIDTH && countchars<=filesize && validfile==true)
		{
			c = infile.get();
			if (c != '\n' && c != '#' && c != ' ' && c != '@' && c != '&' && c != '$' && c != '%' && !(infile.eof()))
				validfile = false; 
			ReadChar(c, row,col,countchars); 
			col++; 
			countchars++; 
		}
	}
	if (isPacman == false || isLegend == false)
	{
		validfile = false; 
	}
	RealHeight = row;
	if (RealHeight < 3 || RealWidth < 3)
	{
		validfile = false;
	}
	if (validfile == true)
	{
		CountFood();
		initLegend();
	}
	else
	{
		isLegend = false; 
		isPacman = false;
		num_of_ghost = 0; 
		system("cls");
	}
	infile.close();
}
void board::CountFood()
{
	for (int i = 0; i < RealHeight; i++)
	{
		for (int j = 0; j < RealWidth; j++)
		{
			if (Board[i][j] == '*')
				num_of_bread++;
		}
	}
}
void board::initLegend()
{
	int row = YlegendPos;
	int col = XlegendPos;
	for (int i = XlegendPos; i < XlegendPos + 3; i++)
		for (int j = YlegendPos; j < YlegendPos + 20; j++)
			Board[i][j] = ' ';
}
void board::ReadChar(char c,int & row, int & col, int &countchar)
{
	switch (c)
	{ 
	case '\n': 
		if (row == 0)
			RealWidth = col;
		else
			while (col < RealWidth)
		    {
			Board[row][col] = ' ';
			col++;
		    }
		row++; 
		col=-1; 
		countchar++; 
		break; 
	case '#':
		Board[row][col] = (unsigned char)178;
		break;
	case ' ':
	{
		Board[row][col] = '*';
		break;
	}
	case '@':
	{
		if (isPacman == true)
		{
			//there are more than one pacmans-invalid file
			validfile = false; 
		}
		else
		{
			isPacman = true; 
			XPacPos = col;
			YPacPos = row;
			Board[row][col] = ' ';
		}
		break;
	}
	case '$':
	{
		if (num_of_ghost >= 4)
		{
			validfile = false; 
		}
		else
		{
			GhostPos[0][num_of_ghost] = col;
			GhostPos[1][num_of_ghost] = row;
			num_of_ghost++;
			Board[row][col] = '*';
		}
		break;
	}
	case '&':
	{
		if (isLegend == true)
		{
			//there are more than one legends-invalid file
			validfile = false;
		}
		else
		{
			isLegend = true; 
			XlegendPos = row;
			YlegendPos = col;
			Board[row][col] = ' ';
		}
		break; 
	}
	case '%':
	{
		Board[row][col] = ' ';
		break; 
	}
	default:
		break;
	}
}
void board::printboard(bool Setcolor, string& playerchoice)
{
	buildboard(playerchoice); 
	for (int i = 0; i < RealHeight; i++)
	{
		for (int j = 0; j < RealWidth; j++)
		{
			if (Board[i][j] == '*')
			{
				if (Setcolor == true)
				{
					setTextColor(BLUE);
				}
				cout << Board[i][j];
				setTextColor(WHITE);
			}
			else
				cout << Board[i][j]; 
		}
		cout << endl; 
	}
	gotoxy(YlegendPos, XlegendPos);
	cout << "LIFES:" << endl;
	gotoxy(YlegendPos, XlegendPos + 1);
	cout << "SCORE:" << endl;
}
