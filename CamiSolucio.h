#pragma once
#include "CamiBase.h"
using namespace std;
class CamiSolucio : public CamiBase
{
public:
	CamiSolucio() {}
	CamiSolucio(const CamiSolucio& c);
	void afegeixPunt(Coordinate cord) { m_CamiCoord.push_back(cord); }

	vector<Coordinate> getCamiCoords() { return m_CamiCoord; }
private:
	vector<Coordinate> m_CamiCoord;
};

