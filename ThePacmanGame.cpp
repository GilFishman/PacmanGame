#include "ThePacmanGame.h"
/*init game settings */
void ThePacmanGame::init(bool setcolor,string &playerchoice, bool Silent)
{

	PointOfTime = 0; 
	if (Level > 1 && Level <= num_of_screens)
	{
		score = 0; 
		GameBoard.setNumOfGhost();
		GameBoard.setFood();
	}
	else if (Level== num_of_screens+1)
	{
		life = 3; 
		score = 0;
		Level = 1; 
		p.SetXbody0(GameBoard.getXpac());
		p.SetYbody0(GameBoard.getYpac());
		GameBoard.setNumOfGhost();
		GameBoard.setFood();
	}
	if (Silent == true)
	{
		GameBoard.buildboard(playerchoice);
	}
	else
	{
		GameBoard.printboard(setcolor, playerchoice);
		gotoxy(6, GameBoard.getRealHeight());
		cout << life;
		gotoxy(6, GameBoard.getRealHeight() + 1);
		cout << score;
		if (setcolor == true)
		{
			p.setColor(YELLOW);
			f.setColor(GREEN);
		}
	}
	p.setArrowKeys("wWzZaAdDsS");
	p.setFigure('@');
	p.setDirection(UP);
	p.SetXbody0(GameBoard.getXpac());
	p.SetYbody0(GameBoard.getYpac());
	p.setBody(1, 0);
	for (int i = 0; i < GameBoard.getNumOfGhost(); i++)
	{
		g[i].SetXbody0(GameBoard.getGhostPos(0, i));
		g[i].SetYbody0(GameBoard.getGhostPos(1, i));
		g[i].setDirection(DOWN);
		g[i].setFigure('&');
		g[i].setBody(1, 0);
		if (setcolor == true)
			g[i].setColor(RED);
	}
}
/*The main function of the game*/
void ThePacmanGame::run(bool setcolor,bool simple)
{
	char key = 0;
	int dir=1;
	int remainfood = GameBoard.getNumOfFood();
	bool isFruit = false; 
	int tillfruit = f.getRenew();
	int isfruitalive=1;
	int height = GameBoard.getRealHeight();
	int width = GameBoard.getRealWidth();
	int stepsTillDummy = 20;
	int stepTillSmart = 0; 
	bool IsGhostSmart = true; 
	srand(time(NULL));
	do {
		if (_kbhit())
		{
			key = _getch();
			if (key == ESC)
			{
				gotoxy(0, GameBoard.getRealHeight() + 3);
				cout << "press ESC again to continue"; 
				key = _getch();
				while (key != ESC)
				{
					key = _getch();
				}
				gotoxy(0, GameBoard.getRealHeight() + 3);
				cout << "                               ";
			}
			if ((dir = p.getDirection(key)) != -1)
				p.setDirection(dir);
		}

		/*in case we need to set new fruit*/
		if (isFruit == false)
		{
			if (tillfruit == 0)
			{
				isFruit = true;
				f.setDirection(rand() % 7);
				f.setValue();
				char fval = f.getValue();
				f.setFigure(fval);
				f.SetXbody0(rand() % (width-2) + 1);
				f.SetYbody0(rand() % (height-2) + 1);
				char FruitposChar = GameBoard.getSymbol(f.getXbody(0), f.getYbody(0));
				f.SetXbody1(f.getXbody(0));
				f.SetYbody1(f.getYbody(0));
				isfruitalive = f.getLifeTime();
				initFruit(); 
			}
			else
				tillfruit--;
		}
		else //isfruit==true
		{
			if (isfruitalive == 0)
			{
				isFruit = false; //need to write to file
			    if (simple == false)
					DisappearanceFruit();
				char FruitPos = GameBoard.getSymbol(f.getXbody(0), f.getYbody(0));
				if (FruitPos == '*')
				{
					if (setcolor == true)
						setTextColor(BLUE);
					f.getBody(0).draw('*');
				}
				else if (FruitPos == ' ')
					f.getBody(0).draw(' ');
				tillfruit = f.getRenew();
			}
			else
			{
				if (fruitSpeed == true)
				{
					char FPosCur1 = GameBoard.getSymbol(f.getXbody(0), f.getYbody(0));
					char FPosNext1 = GameBoard.getSymbol(f.getXbody(1), f.getYbody(1));
					f.move(FPosCur1, FPosNext1, setcolor,height,width, GameBoard,false);
					if (simple == false)
						MoveFruitToFile();
					fruitSpeed = false;
					if (fruitNpac(f.getValue(),setcolor) == true || fruitNghost() == true)
					{
						isFruit = false;
						tillfruit = f.getRenew();
						isfruitalive = 0;
					}
					else
						isfruitalive--;
				}
				else
				{
					fruitSpeed = true;
					if (fruitNpac(f.getValue(),setcolor) == true || fruitNghost() == true)
					{
						isFruit = false;
						tillfruit = f.getRenew();
						isfruitalive = 0;
					}
					else
						isfruitalive--;
				}
			}

		}

		/*The pacman and the ghosts move functions uses the next and the curr positions*/
		int nextPosX = p.getXbody(1);
		int nextPosY = p.getYbody(1); 
		int currPosX= p.getXbody(0);
		int currPosY = p.getYbody(0);
		char PacPos = GameBoard.getSymbol(nextPosX,nextPosY);
		char CurrPacPos = GameBoard.getSymbol(currPosX, currPosY); 
		//the ghosts array saves the curr and next symbols
		char GposSymbol[2][4];
		for (int i = 0; i < GameBoard.getNumOfGhost(); i++)
		{
			GposSymbol[0][i] = GameBoard.getSymbol(g[i].getXbody(0), g[i].getYbody(0));
			GposSymbol[1][i] = GameBoard.getSymbol(g[i].getXbody(1), g[i].getYbody(1));
		}
		/*updating score and food*/
		if (CurrPacPos == '*')
		{
			score++;
			remainfood--; 
			gotoxy(6, GameBoard.getRealHeight() + 1);
			if (setcolor == true)
				setTextColor(WHITE);
			cout << score;
			GameBoard.updatePos(p.getXbody(0), p.getYbody(0));
		}
		/*hits the wall and waiting to a new direction*/
		else if (PacPos == (char)178)
		{
			dir = Stop;
		}
		p.move(setcolor,PacPos, height, width,false);
		if (simple == false)
		{
			MovePacToFile(); //writing to the file the movement
			PointOfTime++;
		}

		/*controlling the speed of the ghosts*/
		if (GhostSpeed == true)
		{
			for (int i = 0; i < GameBoard.getNumOfGhost(); i++)
			{
				if (GhostLevel == 'C')
				{
					g[i].move(GposSymbol[0][i], GposSymbol[1][i], setcolor, height, width, GameBoard,false);
					if (simple == false)
						MoveGhostToFile(i); 
				}
				else if (GhostLevel == 'A')
				{
					g[i].moveSmartGhost(GposSymbol[0][i], GposSymbol[1][i], setcolor, height, width, GameBoard, p.getBody(0));
					if (simple == false)
						MoveGhostToFile(i);
				}
				else if (GhostLevel == 'B')
				{
					if (IsGhostSmart == true)
					{
						if (stepsTillDummy == 0)
						{
							IsGhostSmart = false; 
							g[i].move(GposSymbol[0][i], GposSymbol[1][i], setcolor, height, width, GameBoard,false);
							if (simple == false)
								MoveGhostToFile(i);
							stepTillSmart = 5; 
						}
						else
						{
							g[i].moveSmartGhost(GposSymbol[0][i], GposSymbol[1][i], setcolor, height, width, GameBoard, p.getBody(0));
							if (simple == false)
								MoveGhostToFile(i);
							stepsTillDummy--;
						}
					}
					else //the ghost is dummy
					{
						if (stepTillSmart == 0)
						{
							IsGhostSmart = true; 
							stepsTillDummy = 20; 
							g[i].moveSmartGhost(GposSymbol[0][i], GposSymbol[1][i], setcolor, height, width, GameBoard, p.getBody(0));
							if (simple == false)
								MoveGhostToFile(i);
						}
						else
						{
							g[i].move(GposSymbol[0][i], GposSymbol[1][i], setcolor, height, width, GameBoard,false);
							if (simple == false)
								MoveGhostToFile(i);
							stepTillSmart--; 
						}
					}
				}
				checkMeeting(PacPos, GposSymbol[0][i], GposSymbol[1][i], setcolor, i,simple);
			}
			GhostSpeed = false;
		}
		else
		{
			GhostSpeed = true;
			for (int i = 0; i < GameBoard.getNumOfGhost(); i++)
			{
				checkMeeting(PacPos, GposSymbol[0][i], GposSymbol[1][i], setcolor, i,simple);
			}

		}
		Sleep(200);
	} while (remainfood!=0 && life!=0);

	if (setcolor == true)
		setTextColor(WHITE);

	/*the pacman ate all the food and won!*/
	if (remainfood==0)
	{
		if (simple==false)
			EndOfscreenToFile();
		if (Level == num_of_screens)
		{
			system("CLS");
			cout << "YOU WON! CONGRATULATIONS!" << endl;
			Level++; 
			Sleep(1000); 
		}
		else
		{
			system("CLS");
			Level++; 
		};

	}
	/*the pacman hits a ghost 3 times*/
	if (life == 0)
	{
		if (simple == false)
			EndOfscreenToFile();
		system("CLS");
		cout << "GAME OVER!!" <<endl; 
		Sleep(1000);
	}
	if (simple == false)
	{
		stepsFile.close();
		resultFile.close();
	}
}
/*the function checks if the pacman hits a ghost*/
void ThePacmanGame::checkMeeting(char PacPos, char GPosCur, char GPosNext, bool setcolor, int index, bool simple)
{
	if (g[index].getXbody(0) == p.getXbody(0) && g[index].getYbody(0) == p.getYbody(0))
	{
		//writing to the file
		if (simple == false)
			PacAndGhostToFile();
		life--;
		gotoxy(6, GameBoard.getRealHeight());
		if (setcolor == true)
			setTextColor(WHITE);
		cout << life;
		gotoxy(p.getXbody(0), p.getYbody(0));
		cout << PacPos;
		if (setcolor==true)
			setTextColor(BLUE);
		/*reseting all the locations of the members*/
		p.SetXbody1(GameBoard.getXpac());
		p.SetYbody1(GameBoard.getYpac());
		p.setBody(0, 1);
		PacPos = GameBoard.getSymbol(p.getXbody(1), p.getYbody(1));
		for (int i = 0; i < GameBoard.getNumOfGhost(); i++)
		{
			if (setcolor == true)
				setTextColor(BLUE);
			gotoxy(g[i].getXbody(0), g[i].getYbody(0));
			cout << GameBoard.getSymbol(g[i].getXbody(0), g[i].getYbody(0));
			g[i].SetXbody1(GameBoard.getGhostPos(0, i));
			g[i].SetYbody1(GameBoard.getGhostPos(1, i));
			g[i].setBody(0, 1);
			GPosCur = GameBoard.getSymbol(g[i].getXbody(0), g[i].getYbody(0));
			GPosNext = GameBoard.getSymbol(g[i].getXbody(1), g[i].getYbody(1));
		}
	}
}
bool ThePacmanGame:: fruitNpac(char fruitfigure, bool setcolor)
{
	if ((p.getXbody(0) == f.getXbody(0)) && (p.getYbody(0) == f.getYbody(0)))
	{
		if (fruitfigure == '5')
			score += 5;
		if (fruitfigure == '6')
			score += 6;
		if (fruitfigure == '7')
			score += 7;
		if (fruitfigure == '8')
			score += 8;
		if (fruitfigure == '9')
			score += 9;
		gotoxy(6, GameBoard.getRealHeight() + 1);
		if (setcolor==true)
			setTextColor(WHITE);
		cout << score;
		GameBoard.updatePos(f.getXbody(0), f.getYbody(0));
		return true;
	}
	return false; 
}
bool ThePacmanGame::fruitNghost()
{
	for (int i = 0; i < GameBoard.getNumOfGhost(); i++)
	{
		int currposX = g[i].getXbody(0);
		int currposY = g[i].getYbody(0);
		if (currposX == f.getXbody(0) && currposY == f.getYbody(0))
		{
			if (GameBoard.getSymbol(f.getXbody(0), f.getYbody(0)) == '*')
			{
				f.getBody(0).draw('*'); 
			}
			else
				GameBoard.updatePos(f.getXbody(0), f.getYbody(0));
			return true;
		}
	}
	return false;
}
char ThePacmanGame:: printMenu(int numoffiles)
{
	cout << "Welcome to PACMAN GAME!" << endl;
	printOptions(); 
	int userSel; 
	cin >> userSel;
	char screenchoice; 
	bool startgame = false; 
	
	while (userSel != 1 && userSel != 2 && userSel != 3 && userSel != 4 && userSel != 8 && userSel != 9 &&(!startgame))
	{
		cout << "Wrong key! Pless choose again:" << endl;
		cin >> userSel;
	}
	if (userSel == 8)
	{
		cout << "To play the PACMAN game use the folowing keys: " << endl;
		cout << "a or A : LEFT\nd or D : RIGHT\nw or W : UP\nx or X : DOWN\ns or S : STAY" << endl << endl;
		printOptions();
		cin >> userSel;
	}
	if (userSel == 1)
	{
		choseGhostLevel();
		SetColor=false;
		screenchoice = '0'; 
		startgame = true; 
		system("CLS");
	}
	if (userSel == 2)
	{
		choseGhostLevel();
		SetColor = true;
		screenchoice = '0';
		startgame = true;
		system("CLS");
	}
	if (userSel == 3)
	{
		choseGhostLevel();
		SetColor = false;
		cout << "please choose a number between 1-" << numoffiles << endl;
		cin >> screenchoice;
		startgame = true;
	}
	if (userSel == 4)
	{
		choseGhostLevel();
		SetColor = true;
		cout << "please choose a number between 1-" << numoffiles << endl;
		cin >> screenchoice;
		startgame = true;
	}
	if (userSel == 9)
		return 'F';
	system("cls"); 
	return screenchoice; 
}
void ThePacmanGame::printOptions()
{
	cout << "Please select:" << endl;
	cout << "1.Start a new game without colors" << endl;
	cout << "2.Start a new game with colors" << endl;
	cout << "3.Start a new game with specific screen without colors" << endl;
	cout << "4.Start a new game with specific screen with colors" << endl;
	cout << "8.Present instructions and keys" << endl;
	cout << "9.EXIT" << endl;
}
int ThePacmanGame::ReadFiles(vector<string>& gameFiles)
{
	int AllFiles = 0;
	int found;
	int numOfFiles = 0;
	string str = ".screen";
	string path = ".";
	ifstream screenFile;
	vector<string> files;
	for (const auto& screenFile : directory_iterator(path))
	{
		files.push_back(screenFile.path().string());
		AllFiles++;
	}
	for (int i = 0; i < AllFiles; i++)
	{
		if ((found = files[i].find("screen")) < 0)
		{
			files[i].erase();
		}
		else
		{
			numOfFiles++;
			gameFiles.push_back(files[i]);
		}
	}
	return numOfFiles; 
}
void ThePacmanGame::choseGhostLevel()
{
	cout << "Please select ghost level:" << endl;
	cout << "A-Best" << endl;
	cout << "B-Good" << endl;
	cout << "C-Novice" << endl;
	char c; 
	cin >> c; 
	while (c != 'A' && c != 'B' && c != 'C')
	{

		cout << "Wrong choice! Please chose again:" << endl;
		cin >> c; 
	}
	GhostLevel = c; 
}
void ThePacmanGame::initStepsFile()
{
	string str = "Pacman_0"; 
	string path = ".steps"; 
	str.push_back(Level+'0'); 
	str.append(path); 
	stepsFile.open(str,ios::out | ios ::trunc);
	stepsFile << "Height-" << GameBoard.getRealHeight() << " " << "Width-" << GameBoard.getRealWidth() << " "; 
	stepsFile << "Level-" << Level << " "; 
	stepsFile << "Life-" << life << " "; 
	stepsFile << "Ghost Level " << GhostLevel << " "; 
	stepsFile << "Num of ghost-" << GameBoard.getNumOfGhost() << " "; 
	for (int i = 0; i < GameBoard.getNumOfGhost(); i++)
	{
		stepsFile << "Ghost" << i << " Location: " << GameBoard.getGhostPos(0, i) << " " << GameBoard.getGhostPos(1, i) << " ";
	}
	stepsFile << "Pacman location- " << GameBoard.getXpac() << " " << GameBoard.getYpac() << endl; 
}
void ThePacmanGame::initFruit()
{
	stepsFile <<"FA." << f.getValue(); 
	stepsFile << "." << f.getXbody(0) << "," << f.getYbody(0) << " "; 
}
void ThePacmanGame::DisappearanceFruit()
{
	stepsFile << "FD "; 
}
void ThePacmanGame::MovePacToFile()
{
	stepsFile << "P." << p.getDir() << " "; 
}
void ThePacmanGame::MoveFruitToFile()
{
	stepsFile << "F." << f.getDir() << " "; 
}
void ThePacmanGame::MoveGhostToFile(int i)
{
	stepsFile << "G" <<i << "." << g[i].getDir() << " ";
}
void ThePacmanGame::PacAndGhostToFile()
{
	stepsFile << "GAP "; 
}
void ThePacmanGame::EndOfscreenToFile()
{
	string str = "Pacman_0";
	string path = ".result";
	str.push_back(Level + '0');
	str.append(path);
	resultFile.open(str, ios::out | ios::trunc);
	if (life == 0)
	{
		resultFile << "D" << endl; //D=dead
		resultFile << "POT " << PointOfTime << " "; //points of time
	}
	else
	{
		if (Level == num_of_screens)
		{
			resultFile << "W" << endl; //winnig the game
			resultFile << "POT " << PointOfTime << " ";
		}
		else
		{
			resultFile << "M" << endl; //moving to next screen
			resultFile << "POT " << PointOfTime << " ";
		}
	}
}

void ThePacmanGame::runLoadMode(bool setcolor,string &fileName) //not silent 
{
	ifstream infile;
	infile.open(fileName, ios::out);
	string firstline;
	getline(infile,firstline); 
	string s; 
	infile >> s; 
	while (!infile.eof())
	{
		if (s[0] == 'F') //fruit
		{
			if (s[1] == 'A') //FA.V.x,y
			{
				f.LoadValue((int)(s[3] - '0'));
				f.SetXbody0(s[5]-'0');
				f.SetYbody0(s[7]-'0');
			}
			else if (s[1] == 'D') //fruit disappear
			{
				char FruitPos = GameBoard.getSymbol(f.getXbody(0), f.getYbody(0));
				if (FruitPos == '*')
				{
					f.getBody(0).draw('*');
				}
				else if (FruitPos == (char)178)
					f.getBody(0).draw(unsigned char(178));
				else if (FruitPos == ' ')
					f.getBody(0).draw(' ');
			}
			else
			{
				int dir = s[2] - '0';
				f.setDirection(dir); 
				char FruitPos = GameBoard.getSymbol(f.getXbody(0), f.getYbody(0));
				char next = GameBoard.getSymbol(f.getXbody(1), f.getYbody(1));
				f.move(FruitPos, next, setcolor, GameBoard.getRealHeight(), GameBoard.getRealWidth(), GameBoard,false); 
			}
		}

		else if (s[0] == 'P')
		{

			int dir = s[2] - '0';
			char PacPos = GameBoard.getSymbol(p.getXbody(1), p.getYbody(1));
			char CurrPacPos = GameBoard.getSymbol(p.getXbody(0), p.getYbody(0));
			p.setDirection(dir); 
			if (CurrPacPos == '*')
			{
				score++;
				gotoxy(6, GameBoard.getRealHeight() + 1);
				if (setcolor == true)
					setTextColor(WHITE);
				cout << score;
				GameBoard.updatePos(p.getXbody(0), p.getYbody(0));
			}
			p.move(setcolor, PacPos, GameBoard.getRealHeight(), GameBoard.getRealWidth(),false); 
		} //pacman

		else if (s[0] == 'G')
		{
			if (s[1] == 'A')
			{
				char PacPos = GameBoard.getSymbol(p.getXbody(1), p.getYbody(1));
				life--;
				gotoxy(6, GameBoard.getRealHeight());
				if (setcolor == true)
					setTextColor(WHITE);
				cout << life;
				gotoxy(p.getXbody(0), p.getYbody(0));
				cout << PacPos;
				if (setcolor == true)
					setTextColor(BLUE);
				/*reseting all the locations of the members*/
				p.SetXbody1(GameBoard.getXpac());
				p.SetYbody1(GameBoard.getYpac());
				p.setBody(0, 1);
				PacPos = GameBoard.getSymbol(p.getXbody(1), p.getYbody(1));
				for (int i = 0; i < GameBoard.getNumOfGhost(); i++)
				{
					if (setcolor == true)
						setTextColor(BLUE);
					gotoxy(g[i].getXbody(0), g[i].getYbody(0));
					cout << GameBoard.getSymbol(g[i].getXbody(0), g[i].getYbody(0));
					g[i].SetXbody1(GameBoard.getGhostPos(0, i));
					g[i].SetYbody1(GameBoard.getGhostPos(1, i));
					g[i].setBody(0, 1);
					char GPosCur = GameBoard.getSymbol(g[i].getXbody(0), g[i].getYbody(0));
					char GPosNext = GameBoard.getSymbol(g[i].getXbody(1), g[i].getYbody(1));
				}
			}
			else
			{
				int dir = s[3] - '0';
				int index = s[1] - '0';
				g[index].setDirection(dir);
				char GhostPos = GameBoard.getSymbol(g[index].getXbody(0), g[index].getYbody(0));
				char next = GameBoard.getSymbol(g[index].getXbody(1), g[index].getYbody(1));
				g[index].move(GhostPos, next, setcolor, GameBoard.getRealHeight(), GameBoard.getRealWidth(), GameBoard,false);
			}
		} //ghost 

		infile >> s;
		Sleep(100); 
	}
	if (life == 0)
	{
		system("cls"); 
		exit(1); 
	}
	score = 0; 
}
void ThePacmanGame::runSilentMode(string& fileName, string &resultfile) 
{
	int countSteps = 0;
	ifstream infile;
	infile.open(fileName, ios::out);
	string firstline;
	getline(infile, firstline);
	string s;
	infile >> s;
	while (!infile.eof())
	{
		if (s[0] == 'F') //fruit
		{
			if (s[1] == 'A') //FA.V.x,y
			{
				f.LoadValue((int)(s[3] - '0'));
				f.SetXbody0(s[5]-'0');
				f.SetYbody0(s[7]-'0');
			}
			else if (s[1] == 'D') //fruit disappear
			{
				char FruitPos = GameBoard.getSymbol(f.getXbody(0), f.getYbody(0));
				GameBoard.SetPos(f.getXbody(0), f.getYbody(0),FruitPos); 
			}
			else
			{
				int dir = s[2] - '0';
				char FruitPos = GameBoard.getSymbol(f.getXbody(0), f.getYbody(0));
				char next = GameBoard.getSymbol(f.getXbody(1), f.getYbody(1));
				GameBoard.SetPos(f.getXbody(0), f.getYbody(0), FruitPos);
				f.move(FruitPos, next, false, GameBoard.getRealHeight(), GameBoard.getRealWidth(), GameBoard, true);
		//		f.SilentMove(dir, GameBoard.getRealHeight(), GameBoard.getRealWidth());
			}
		}

		else if (s[0] == 'P')
		{

			int dir = s[2] - '0';
			char PacPos = GameBoard.getSymbol(p.getXbody(1), p.getYbody(1));
			char CurrPacPos = GameBoard.getSymbol(p.getXbody(0), p.getYbody(0));
			GameBoard.SetPos(p.getXbody(0), p.getYbody(0), PacPos);
			if (CurrPacPos == '*')
			{
				score++;
				GameBoard.updatePos(p.getXbody(0), p.getYbody(0));
			}
			p.move(false, PacPos, GameBoard.getRealHeight(), GameBoard.getRealWidth(), true);
	//		p.SilentMove(dir, GameBoard.getRealHeight(), GameBoard.getRealWidth());
			countSteps++; 
		} //pacman

		else if (s[0] == 'G')
		{
			if (s[1] == 'A')
			{
				char PacPos = GameBoard.getSymbol(p.getXbody(1), p.getYbody(1));
				life--;
				/*reseting all the locations of the members*/
				p.SetXbody1(GameBoard.getXpac());
				p.SetYbody1(GameBoard.getYpac());
				p.setBody(0, 1);
				PacPos = GameBoard.getSymbol(p.getXbody(1), p.getYbody(1));
				for (int i = 0; i < GameBoard.getNumOfGhost(); i++)
				{
					g[i].SetXbody1(GameBoard.getGhostPos(0, i));
					g[i].SetYbody1(GameBoard.getGhostPos(1, i));
					g[i].setBody(0, 1);
					char GPosCur = GameBoard.getSymbol(g[i].getXbody(0), g[i].getYbody(0));
					char GPosNext = GameBoard.getSymbol(g[i].getXbody(1), g[i].getYbody(1));
				}
			}
			else
			{
				int dir = s[3] - '0';
				int index = s[1] - '0';
				g[index].setDirection(dir);
				char GhostPos = GameBoard.getSymbol(g[index].getXbody(0), g[index].getYbody(0));
				char next = GameBoard.getSymbol(g[index].getXbody(1), g[index].getYbody(1));
				GameBoard.SetPos(g[index].getXbody(0), g[index].getYbody(0), GhostPos);
				g[index].move(GhostPos, next, false, GameBoard.getRealHeight(), GameBoard.getRealWidth(), GameBoard, true);
			}
		
		//	g[index].SilentMove(dir, GameBoard.getRealHeight(), GameBoard.getRealWidth());
		} //ghost 

		infile >> s;
	}
	ifstream resFile;
	resFile.open(resultfile, ios::out);
	string resline;
	getline(resFile, resline);
	string r;
	resFile >> r;
	int pot; 
	resFile >> pot; 

	if (pot == countSteps)
	{
		cout << "Test passed!" << endl;
	}
	else
	{
		cout << "Test failed!" << endl; 
	}
}



