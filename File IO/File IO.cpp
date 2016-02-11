// File IO.cpp : Defines the entry point for the console application.
// Simple application to demonstrate classes from <fstream> for file manipulation.

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>

struct ToBeWritten
{
	int ID;
	std::string name;
	std::string content;
};

std::streamoff GetFileSize(std::string filename)
{
	using namespace std;
	ifstream inf(filename);

	inf.seekg(0, ios::end);

	return inf.tellg();
};

void PrintToFile()
{
	using namespace std;

	//ofstream = Output File STREAM
	ofstream outf("sample.dat");

	if (!outf)
	{
		cerr << "Cannot open sample.dat for writing!" << endl;
		exit(1);
	}

	//Writting simple string into the file
	outf << "This is line #1" << endl;
	outf << "This is line #2" << endl;

	//Trying to write a strcuture
	ToBeWritten	data;
	data.ID = 1;
	data.name = "Hello world";
	data.content = "Let me see what will happen once I finnish this. I suppose I might get an error.";
	
	outf << data.ID + ";" + data.name + ";" + data.content << endl;

	return;
	//When outf goes out of scope, the ofstream destructor will close it automatically.
};

void ReadFromFile()
{
	using namespace std;

	ifstream inf("sample.dat");

	if (!inf)
	{
		cerr << "Cannot open sample.dat for reading!" << endl;
	}

	while (inf)
	{
		string strInput;
		getline(inf, strInput);
		cout << strInput << endl;
	};

	return;
};


int _tmain(int argc, _TCHAR* argv[])
{
	PrintToFile();

	ReadFromFile();

	std::cout << GetFileSize("sample.dat") << std::endl;
}

