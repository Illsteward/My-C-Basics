// Monster printer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>


enum class monsterRaces
{
	OGRE, DRAGON, ORC, GIANT_SPIDER, SLIME
};

using namespace std;
struct Monster
{
	monsterRaces race;
	string name;
	int health;	
};

string GetMyType(Monster ToUse)
{
	switch (ToUse.race)
	{
	case monsterRaces::OGRE:
		return "ogre";
	case monsterRaces::DRAGON:
		return "dragon";
	case monsterRaces::ORC:
		return "orc";
	case monsterRaces::GIANT_SPIDER:
		return "giant spider";
	case monsterRaces::SLIME:
		return "slime";
	default:
		return "Undiscovered Race";
	};
};


void printMonster(Monster ToPrint)
{
	using namespace std;
	
	cout << "Tento " << GetMyType(ToPrint) << " se jmenuje: " << ToPrint.name << " a má " << ToPrint.health << "bodù zdraví." << endl;
};


int _tmain(int argc, _TCHAR* argv[])
{
	Monster ogre = { monsterRaces::OGRE, "Torg", 145 };

	Monster slime = { monsterRaces::SLIME, "Blurp", 23};
	
	printMonster(ogre);
	printMonster(slime);

	return 0;
}

