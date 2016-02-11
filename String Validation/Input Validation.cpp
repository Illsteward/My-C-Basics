// Input Validation.cpp : Defines the entry point for the console application.
// Finally working input validation using standard and preffered C++ method. Yay!

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include "Calculator.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	float intFirst, intSecond;
	string strFirst, strSecond;
	stringstream buffer;
	char operand;
	Calculator StateController = Calculator(0);

	while (1)
	{
		if (StateController.ReportState() == 0)
		{
			cout << "Enter first number:" << endl;
			cin >> strFirst;
		
			// Zkontrolujeme, že všechny znaky jsou èíslice.
			if (isInputANumber(strFirst)) {
				buffer << fixed << strFirst;
				buffer >> intFirst;
			}
			else {
			  	cout << "Your input is not a number. The program will terminate now." << endl;
				break;
			};

		}
		else
		{
			cout << "The last result was: " << StateController.ReportState() << endl;
			cout << "It will be used for this calculation." << endl;
			intFirst = StateController.ReportState();
		}
		cin.clear();
		buffer.clear();
		cout << "Enter second number:" << endl;
		cin >> strSecond;

		if (isInputANumber(strSecond)) {
			buffer << fixed << strSecond;
			buffer >> intSecond;
		} else {
			cout << "Your input is not a number. The program will terminate now." << endl;
			break;
		};
		cin.clear();
		buffer.clear();

		cout << "Enter operation to be performed:" << endl;
		cin >> operand;

		cin.clear();
		buffer.clear();

		cout << "prvni cislo: " << intFirst << endl;
		cout << "druhe cislo: " << intSecond << endl;
		cout << "m_result: " << StateController.ReportState() << endl;

		switch (operand)
		{
		case '+':
			cout << "The sum of provided numbers is: " << StateController.Calculate(intFirst, intSecond, '+') << endl;
			break;
		case '-':
			cout << "The difference of provided numbers is: " << StateController.Calculate(intFirst, intSecond, '-') << endl;
			break;
		case '/':
			if (intSecond != 0)
				cout << "The quotient of provided numbers is: " << StateController.Calculate(intFirst, intSecond, '/') << endl;
			else
				cout << "Cannot divide by zero.";
			break;
		case '*':
			cout << "The product of provided numbers is: " << StateController.Calculate(intFirst, intSecond, '*') << endl;
			break;
		default:
			cout << "Unknown operator. Unable to determine result. Please try again." << endl;
			break;
		};
		buffer.clear();
		cin.clear();
	}
}