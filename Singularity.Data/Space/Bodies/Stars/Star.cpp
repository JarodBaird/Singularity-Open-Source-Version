#include "Star.h"

namespace Singularity
{
	Star::Star(Altair::Color c)
	{
		m_land_color = std::move(c);
		m_sprite_x = 15;
		m_sprite_y = 0;
	}
}
