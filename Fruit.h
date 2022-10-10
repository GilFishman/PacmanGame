#ifndef _FRUIT_H_
#define _FRUIT_H_

#include "Creature.h"
#include <time.h>   
#include <stdlib.h>

class Fruit : public Creature
{
	int value; 
	int lifetime; //number of pacman steps until the fruit disappear  
	int renew; //number of pacman steps until the fruit appear 
	board b; 

public: 
	//ctor
	Fruit() : Creature(0, 0) {};
	//methods
	void move(char curr, char next, bool Setcolor, int height, int width, board& Board, bool isSilent);
	//getters andd setters
	void setValue()
	{
		srand(time(NULL));
		value = rand() % 5+5; 
	}
	void LoadValue(int val)
	{
		value = val; 
	}
	const char getValue()
	{
		return (char)(value) +'0';
	}
	const int getLifeTime()
	{
		srand(time(NULL));
		lifetime = rand() % 50; 
		return lifetime; 
	}
	const int getRenew()
	{
		srand(time(NULL));
		renew= rand() % 100;
		return renew;
	}
	
};

#endif