// Multiple Files.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "io.h"

int _tmain(int argc, _TCHAR* argv[])
{
	int a;
	int b;
	a = readNumber();
	b = readNumber();
	writeAnswer(a + b);
	return 0;
}

