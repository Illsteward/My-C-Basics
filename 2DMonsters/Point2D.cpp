#include "stdafx.h"
#include <iostream>

class Point2D
{
private:
	int m_X;
	int m_Y;

public:
	Point2D() : m_X(0), m_Y(0) {}; //V�choz� konstruktor t��dy
	Point2D(int X, int Y) : m_X(X), m_Y(Y){}; //Konstruktor s parametry


	//P�et�en� oper�toru << pro v�stup do toku. V podstat� speci�ln� "print" funkce
	friend std::ostream& operator<< (std::ostream& out, const Point2D &cPoint)
	{
		out << "(" << cPoint.GetX() << ", " << cPoint.GetY() << ")";
		return out;
	}

	//Setter
	void SetPoint(int X, int Y)
	{
		m_X = X;
		m_Y = Y;
	}

	//Gettery
	int GetX() const { return m_X; }
	int GetY() const { return m_Y; }
};