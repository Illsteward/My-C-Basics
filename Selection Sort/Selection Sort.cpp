// Selection Sort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>


int _tmain(int argc, _TCHAR* argv[])
{
	const int nSize = 6;

	int pole[nSize] = { 30, 60, 20, 50, 40, 10 };

	for (int nStartIndex = 0; nStartIndex < nSize; nStartIndex++)
	{

		int nSmallestIndex = nStartIndex;

		for (int nCurrentIndex = nStartIndex; nCurrentIndex < nSize; nCurrentIndex++)
		{
			if (pole[nCurrentIndex] < pole[nSmallestIndex])
			{
				nSmallestIndex = nCurrentIndex;
			}
		}

		std::swap(pole[nSmallestIndex], pole[nStartIndex]);

		std::cout << "Momentalni stav pole: ";
		for (int CurrentToPrint = 0; CurrentToPrint < nSize; CurrentToPrint++)
		{
			std::cout << pole[CurrentToPrint] << " ";
		};
		std::cout << std::endl;

	}

	return 0;
}

