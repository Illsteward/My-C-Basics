#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include "Calculator.h"

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


float Calculator::Addition(float a, float b)
{
	return a + b;
};

float Calculator::Substraction(float a, float b)
{
	return a - b;
};

float Calculator::Multiplication(float a, float b)
{
	return a * b;
}

float Calculator::Division(float a, float b)
{
	if (b != 0)
	{
		return a / b;
	}
			else
			{
				cout << "Can't divide by zero!";
				return 0;
			};
		}

Calculator::Calculator(float initialize) : m_result(initialize) {};

float Calculator::Calculate(float a, float b, char op)
{
	switch (op)
	{
		case '+':
			m_result = Addition(a, b);
			break;
		case '-':
			m_result = Substraction(a, b);
			break;
		case '*':
			m_result = Multiplication(a, b);
			break;
		case '/':
			m_result = Division(a, b);
			break;
		default:
			m_result = 0;
		};

	return m_result;
};

void Calculator::SetResult(float value)
{
	m_result = value;
}

void Calculator::ResetCounter()
{
	m_result = 0;
}

float Calculator::ReportState()
{
	return m_result;
}