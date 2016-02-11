//Program nechá uživatele zadat velikost pole, které následnì inicializuje a naplní èísly od 0 do X

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

bool isInputANumber(string input)
{
	for (unsigned int nIndex = 0; nIndex < input.length(); nIndex++)
	{
		if (!isdigit(input[nIndex]) && (input[nIndex] != '.') && (input[nIndex] != ','))
		{
			return false;
		}
	} return true;
};

int main()
{
	string s;
	int boundary;
	int * Pole;

	while (true)
	{
		cout << "Zadej velikost pole:" << endl;
		getline(cin, s);
		if (!isInputANumber(s)) {
			cout << "Nebylo zadáno èíslo. Program se nyní ukonèí.";
			break;
		};
		cout << "Zadaná hranice: " << boundary << endl;
		if (boundary < 1)
		{
			cout << "Hranice pole zadána nižší než 1. Nastavuji na 1." <<	endl;
			boundary = 1;
		};
		Pole = new int[boundary];
		for (int i = 0; i < boundary; i++)
		{
			Pole[i] = i;
			cout << "Nastavuji pozici " << i << " v poli na :" << Pole[i] << endl;
		};
	};
	delete[] Pole;
};