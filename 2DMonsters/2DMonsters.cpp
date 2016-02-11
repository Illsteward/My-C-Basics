// 2DMonsters.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include "Monster.h"

int _tmain(int argc, _TCHAR* argv[])
{
	using namespace std;
	cout << "Enter a name for your creature: ";
	std::string cName;
	cin >> cName;
	Creature cCreature(cName, Point2D(4, 7));

	while (1)
	{
		cout << cCreature << endl;
		cout << "Enter new X location for creature (-1 to quit): ";
		int nX = 0;
		cin >> nX;
		if (nX == -1)
			break;

		cout << "Enter new Y location for creature (-1 to quit): ";
		int nY = 0;
		cin >> nY;
		if (nY == -1)
			break;

		cCreature.MoveTo(nX, nY);
	}

	return 0;
}


