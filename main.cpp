#include <Windows.h>
#include <iostream>

using namespace std;

#include "ThePacmanGame.h"

int main(int argc, char * argv[])
{
	ThePacmanGame game;
	bool stop = false; 
	vector <string> GameFiles; 
	int totalFiles; 
	totalFiles= game.ReadFiles(GameFiles);
	// if there are no files we cant run the game
	if (totalFiles == 0)
	{
		cout << "There are no files! please add files before try again"; 
		Sleep(1000);
		return 0; 
	}
	char FirstScreen; 
	int numofscreen = 1; 
	int i = 0; 
	if (argc > 3)
		return 0; 
	if (argc > 1 && argv[1][0] != '-')
		return 0;
	if (argc > 1 && strcmp(argv[1], "-load") != 0 && strcmp(argv[1], "-save") != 0)
		return 0; 
	if (argc ==3 && strcmp(argv[2], "[-silent]") != 0)
		return 0;

	if (argc == 1)//simple mode
	{
		while (stop == false) 
		{
			FirstScreen = game.printMenu(GameFiles.size());
			if (FirstScreen == '0')
			{
				for (i = 0; i < GameFiles.size(); i++)
				{
					int size = GameFiles.size();
					game.setNumOfScreens(GameFiles.size());
					game.init(game.GetColor(), GameFiles[i],false);
					if (game.GetIsValid() == false)
					{
						system("cls");
						cout << "There is a problem with screen number " << i + 1 << " moving to the next screen" << endl;
						Sleep(2000);
						system("cls");
					}
					else
					{
						game.run(game.GetColor(),true);
						system("CLS");
					}
				}
			}
			else if (FirstScreen == 'F')
				return 0; 
			else 
			{
				game.setNumOfScreens(1);

				i = FirstScreen - '0';
				game.init(game.GetColor(), GameFiles[(int)i - 1],false);
				if (game.GetIsValid() == false)
				{
					system("cls");
					cout << "Invalid file!";
					Sleep(1000);
					return 0;
				}
				game.run(game.GetColor(),true);
				system("CLS");
			}
			stop = false;
		}
	}

	else if (argc == 2)//load mode
	{
		if (strcmp(argv[1], "-load") == 0) //load mode
		{
			for (i = 0; i < GameFiles.size(); i++)
			{
				int size = GameFiles.size();
				game.setNumOfScreens(GameFiles.size());
				game.init(game.GetColor(), GameFiles[i], false);
				string str = "Pacman_0";
				string path = ".steps";
				str.push_back(i+1 + '0');
				str.append(path);

				game.runLoadMode(game.GetColor(), str);
				system("CLS");
			}
		}
		else //save mode
		{
			while (stop == false)
			{
				FirstScreen = game.printMenu(GameFiles.size());
				if (FirstScreen == '0')
				{
					for (i = 0; i < GameFiles.size(); i++)
					{
						int size = GameFiles.size();
						game.setNumOfScreens(GameFiles.size());
						game.init(game.GetColor(), GameFiles[i], false);
						game.initStepsFile();
						if (game.GetIsValid() == false)
						{
							system("cls");
							cout << "There is a problem with screen number " << i + 1 << " moving to the next screen" << endl;
							Sleep(2000);
							system("cls");
						}
						else
						{
							game.run(game.GetColor(),false);
							system("CLS");
						}
					}
				}
				else
				{
					game.setNumOfScreens(1);

					i = FirstScreen - '0';
					game.init(game.GetColor(), GameFiles[(int)i - 1], false);
					game.initStepsFile();
					if (game.GetIsValid() == false)
					{
						system("cls");
						cout << "Invalid file!";
						Sleep(1000);
						return 0;
					}
					game.run(game.GetColor(),false);
					system("CLS");
				}
				stop = false;
			}
		}
	}

	else if (argc == 3) //silent
	{
		for (i = 0; i < GameFiles.size(); i++)
		{
			int size = GameFiles.size();
			game.setNumOfScreens(GameFiles.size());
			game.init(game.GetColor(), GameFiles[i], true);
			string str = "Pacman_0";
			string path = ".steps";
			str.push_back(i+1 + '0');
			str.append(path);
			string str2 = "Pacman_0";
			string path2 = ".result";
			str2.push_back(i+1 + '0');
			str2.append(path2);

			game.runSilentMode(str, str2);
		}
	}
}

