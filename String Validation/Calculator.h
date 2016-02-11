#pragma once

#include <string>
using namespace std;

bool isInputANumber(string input);

class Calculator
	{
	private:
		float m_result;
		float Addition(float a, float b);
		float Substraction(float a, float b);
		float Multiplication(float a, float b);
		float Division(float a, float b);
	public:
		float Calculate(float a, float b, char op);
		Calculator(float intialize = 0);
		void SetResult(float value);
		void ResetCounter();
		float ReportState();
	};