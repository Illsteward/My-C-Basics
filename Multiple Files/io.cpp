
#include "stdafx.h"
#include <iostream>

using namespace std;

int readNumber()
{
	int vstup;
	cout << "Zadej cislo:";
	cin >> vstup;
	return vstup;
}

void writeAnswer(int answer)
{
	cout << "Soucet zadanych cisel je:" << answer << endl;
}
