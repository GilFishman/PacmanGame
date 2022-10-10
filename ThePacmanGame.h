#ifndef _THEPACMANGAME_H_
#define _THEPACMANGAME_H_

#include "io_utils.h"
#include "Pacman.h"
#include "board.h"
#include "Ghost.h"
#include "Fruit.h"
#include "Creature.h"
#include <string>
#include <vector>
#include <time.h>
#include <filesystem>
#include <fstream>

using std::filesystem::directory_iterator;

class ThePacmanGame
{
	enum { ESC = 27 };
	Pacman p; 
	Ghost g[4]; 
	Fruit f; 
	int score =0; 
	int life = 3;
	int Level=1;
	board GameBoard;
	bool GhostSpeed = false; 
	bool fruitSpeed = false; 
	vector <string> FilesName;
	string FirstScreen;
	bool SetColor; 
	int num_of_screens;
	char GhostLevel; 
	ofstream stepsFile;
	ofstream resultFile; 
	bool loadmode; 
	int PointOfTime = 0; 

public:
	//methods
	void init(bool setcolor, string& playerchoice, bool Silent);
	void run(bool setcolor,bool simple);
	void checkMeeting(char PacPos, char GPosCur, char GPosNext, bool setcolor, int index,bool simple);
	char printMenu(int numoffiles);
	bool fruitNpac(char fruitfigure, bool setcolor);
	bool fruitNghost();
	void printOptions();
	int ReadFiles(vector<string>& gameFiles);
	void choseGhostLevel(); 
	void initStepsFile(); 
	void initFruit(); 
	void DisappearanceFruit(); 
	void MovePacToFile();
	void MoveGhostToFile(int i);
	void PacAndGhostToFile(); 
	void EndOfscreenToFile();
	void runLoadMode(bool setcolor, string& fileName);
	void MoveFruitToFile();
	void runSilentMode(string& fileName, string& resultfile);

	//getters and setters
	const int getLevel()
	{
		return Level; 
	}
	const bool GetColor()
	{
		return SetColor;
	};
	const int getlife()
	{
		return life;
	};
	const int getNumOfScreens()
	{
		return num_of_screens;
	};
	void setNumOfScreens(int i)
	{
		num_of_screens = i;
	};
	const char GetGhostLevel() 
	{
		return GhostLevel; 
	}
	const bool GetIsValid()
	{
		return GameBoard.getValid();
	}
};
#endif