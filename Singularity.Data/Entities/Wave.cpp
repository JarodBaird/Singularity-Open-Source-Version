#include "Wave.h"

namespace Singularity
{
	Wave::Wave() : Entity()
	{
		m_color = Altair::Color::yellow;
		m_tile = 0xf7;
	}

	void Wave::update() { }
}
