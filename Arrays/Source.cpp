//Program nech� u�ivatele zadat velikost pole, kter� n�sledn� inicializuje a napln� ��sly od 0 do X

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
			cout << "Nebylo zad�no ��slo. Program se nyn� ukon��.";
			break;
		};
		cout << "Zadan� hranice: " << boundary << endl;
		if (boundary < 1)
		{
			cout << "Hranice pole zad�na ni��� ne� 1. Nastavuji na 1." <<	endl;
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