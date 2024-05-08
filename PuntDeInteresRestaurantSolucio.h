#pragma once
#include "PuntDeInteresBase.h"
using namespace std;
class PuntDeInteresRestaurantSolucio : public PuntDeInteresBase
{
public:

	PuntDeInteresRestaurantSolucio(Coordinate cord, string name, string openingHours, bool wheelChair, string cuisine) :
		PuntDeInteresBase(cord, name), m_openingHours(openingHours), m_wheelChair(wheelChair), m_cuisine(cuisine) {}
	string getName() const { return m_name; }
	unsigned int getColor();
	PuntDeInteresRestaurantSolucio* clone() { return new PuntDeInteresRestaurantSolucio(*this); }

private:

	string m_name;
	string m_openingHours;
	bool m_wheelChair;
	string m_cuisine;

};

