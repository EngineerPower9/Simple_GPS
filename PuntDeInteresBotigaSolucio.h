#pragma once
#include "PuntDeInteresBase.h"
using namespace std;
class PuntDeInteresBotigaSolucio : public PuntDeInteresBase
{
public:
	PuntDeInteresBotigaSolucio() : m_shop(""), m_name(""), m_rodes(false) {}
	PuntDeInteresBotigaSolucio(const Coordinate& cord, const string name, const string botiga, const string hores, const bool cadiraRodes) : PuntDeInteresBase(cord, name), m_hores(hores), m_rodes(cadiraRodes), m_shop(botiga) {}
	string getName() const { return m_name; }
	unsigned int getColor();
	//void setName(std::string botiga) { m_shop = botiga; }
	PuntDeInteresBotigaSolucio* clone() { return (new PuntDeInteresBotigaSolucio(*this)); }

private:
	string m_name;
	string m_hores;
	bool m_rodes;
	string m_shop;

};

