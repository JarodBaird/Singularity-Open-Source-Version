#include "AsteroidBelt.h"

namespace Singularity
{
	AsteroidBelt::AsteroidBelt()
	{
		m_width = 1;
		m_land_color = Altair::Color::brown;
		m_sprite_x = 1;
		m_sprite_y = 12;
		m_orbit.semimajor_axis = 10;
		m_terrain_map = nullptr;
	}
}
