// Animals.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>

using namespace std;

class Animal
{
protected:
	string m_strName;

public:
	Animal(string strName) : m_strName(strName) {};
	string GetName() { return m_strName; };
	virtual const char* Speak() = 0;
};

class Cow : public Animal
{
public:
	Cow(std::string strName)
		: Animal(strName)
	{
	}

	// We forgot to redefine Speak - class remains abstract and can not be instanced.
};


class Cat: public Animal
{
public:
	Cat(string strName) : Animal(strName) {};

	const char* Speak() { return "Meow"; };
};

class Goose : public Animal
{
public:
	Goose(string strName) : Animal(strName) {};

	const char* Speak() { return "Gagaga"; };
};

class Horse : public Animal
{
public:
	Horse(string strName) : Animal(strName) {};

	const char* Speak() { return "Ihahaha"; };
};

void Report(Animal &rAnimal)
{
	cout << rAnimal.GetName() << " says " << rAnimal.Speak() << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	Horse Zita("Zita"), Zadar("Zadar"), Zorin("Zorin");
	Goose Retard("Retard"), Pikin("Pikin");
	Cat Macek("Macek"), Tygr("Tygr"), James("James");

	Animal *myAnimals[] = { &Zita, &Zadar, &Zorin, &Retard, &Pikin, &Macek, &Tygr, &James };

	for (int i = 0; i < 8; i++)
	{
		Report( *myAnimals[i] );
	};
	return 0;
}

