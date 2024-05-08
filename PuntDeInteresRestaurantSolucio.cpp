#include "PuntDeInteresRestaurantSolucio.h"



unsigned int PuntDeInteresRestaurantSolucio::getColor()
{
	int color;
	if (m_cuisine == "pizza" && m_wheelChair)
	{
		color = 0x03FCBA;
	}
	else
	{
		if (m_cuisine == "chinese")
		{
			color = 0xA6D9F7;
		}
		else
		{
			if (m_wheelChair)
			{
				color = 0x251351;
			}
			else
			{
				color = PuntDeInteresBase::getColor();;
			}
		}
	}

	return color;
}
