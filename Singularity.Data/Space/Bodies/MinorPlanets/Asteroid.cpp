#include "Asteroid.h"
#include "../../../Terrain/MapTypes/TinyTerrainMap.h"

namespace Singularity
{
	Asteroid::Asteroid()
	{
		m_land_color = Altair::Color::brown;
		m_sprite_x = 15;
		m_sprite_y = 0;

		m_orbit.semimajor_axis = rand() % 50 + 1;
		m_orbit.eccentricity = .2;

		m_name = "Asteroid " + std::to_string(m_orbit.semimajor_axis);

		m_terrain_map = std::make_unique<TinyTerrainMap>();
	}
}
