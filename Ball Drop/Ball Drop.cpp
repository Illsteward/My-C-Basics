// Ball Drop.cpp : Defines the entry point for the console application.
// Bártkùv oblíbený pøíklad - balónek padající z vìže. Spoèítejte výšku v èase T.

#include "stdafx.h"
#include "constants.h"
#include <iostream>
#include <math.h>

using namespace myConstants;
using namespace std;


double dropped(int cas)
{
	double result = (GRAVITY_PULL * pow(cas, 2)) / 2;
	return result;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int vez, cas = 0;
	double zbyva;
	cout << "Zadej vysku veze:" << endl;
	cin >> vez;
	zbyva = (float) vez;
	while (zbyva > 0)
	{
		zbyva = vez - dropped(cas);
		if (zbyva <= 0) 
			cout << "Balonek dopadl na zem v case " << cas << " sekund." << endl;
		else
		{
			cout << "Balonek je ve vzduchu uz " << cas << " sekund. Nachazi se ve vysce: " << zbyva << "metru." << endl;
			cas++;
		}		
	};
	return 0;
}

