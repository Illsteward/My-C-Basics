#include "stdafx.h"
#include <iostream>
#include <string>
#include "Point2D.h"


using namespace std;

class Creature
{
private:
	string m_Name;
	Point2D m_Location;
	Creature() {};

public:
	//Ve�ejn� konstrktor po�aduje u t�to t��dy dva parametry
	Creature(string strName, const Point2D &cLocation) : m_Name(strName), m_Location(cLocation) {};

	//Vytvo�en� frienda pro v�pis informac�.
	friend ostream& operator<<(ostream& out, const Creature &cCreature)
	{
		out << cCreature.m_Name.c_str() << " je na poli " << cCreature.m_Location;
		return out;
	}

	void MoveTo(int nX, int nY)
	{
		m_Location.SetPoint(nX, nY);
	}

};