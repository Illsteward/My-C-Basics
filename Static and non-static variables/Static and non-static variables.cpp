// Static and non-static variables.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

void incrementAndPrint()
{
	using namespace std;
	int value = 1; // automatic duration by default
	++value;
	cout << value << endl;
} // value is destroyed here

void s_incrementAndPrint()
{
	using namespace std;
	static int s_value = 1; // static duration via static keyword.  This line is only executed once.
	++s_value;
	cout << s_value << endl;
} // s_value is not destroyed here, but becomes inaccessible


int main()
{
	std::cout << "Non-static versions:" << std::endl;
	incrementAndPrint();
	incrementAndPrint();
	incrementAndPrint();
	std::cout << "Static versions:" << std::endl;
	s_incrementAndPrint();
	s_incrementAndPrint();
	s_incrementAndPrint();
}


