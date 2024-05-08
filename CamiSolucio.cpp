#include "CamiSolucio.h"

CamiSolucio::CamiSolucio(const CamiSolucio& c)
{
	for (int i = 0; i < c.m_CamiCoord.size(); i++)
	{
		m_CamiCoord.push_back(c.m_CamiCoord[i]);
	}
}