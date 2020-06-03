#include "Comet.h"
#include "../../../Terrain/MapTypes/TinyTerrainMap.h"

namespace Singularity
{
	Comet::Comet()
	{
		m_land_color = Altair::Color::silver;
		m_sprite_x = 11;
		m_sprite_y = 14;

		m_orbit.semimajor_axis = rand() % 50 + 1;
		m_orbit.eccentricity = .9;

		m_name = "Comet " + std::to_string(m_orbit.semimajor_axis);

		m_terrain_map = std::make_unique<TinyTerrainMap>();
	}
}
