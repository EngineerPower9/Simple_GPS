#include "PuntDeInteresBotigaSolucio.h"


using namespace std;
unsigned int PuntDeInteresBotigaSolucio::getColor()
{
	int color;

	if (m_shop == "supermarket")
	{
		color = 0xA5BE00;
	}
	else
	{
		if (m_shop == "bakery")
		{
			if (m_hores.find("06:00-22:00") != std::string::npos && m_rodes)
			{
				color = 0x4CB944;
			}
			else
				color = 0xE85D75;
		}
		else
		{
			if (m_shop == "tobacco")
			{
				color = 0xFFAD69;
			}
			else
			{
				color = 0xEFD6AC;
			}
		}
	}


	return color;

}
