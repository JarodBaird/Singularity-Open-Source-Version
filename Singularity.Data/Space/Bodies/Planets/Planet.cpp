#include "Planet.h"
#include "../../../Terrain/MapTypes/MediumTerrainMap.h"
#include "Singularity.Data/Physics/Chemistry/Gigamole.h"

namespace Singularity
{
	Planet::Planet(std::string name, OrbitData orbit, std::unique_ptr<TerrainMap> terrain)
	{
		m_name = std::move(name);
		m_orbit = orbit;
		m_ocean = nullptr;

		m_sprite_x = 15;
		m_sprite_y = 6;

		m_terrain_map = std::make_unique<MediumTerrainMap>();
		for (uint32_t x = 0; x < terrain->get_map_width(); x++)
		{
			for (uint32_t y = 0; y < terrain->get_map_height(); y++)
			{
				m_terrain_map->set_terrain_height(x, y, terrain->get_terrain_height(x, y));
				m_terrain_map->set_ocean_depth(x, y, terrain->get_ocean_depth(x, y));
				m_terrain_map->set_structure(x, y, terrain->get_structure(x, y));
			}
		}
	}

	void Planet::set_ocean_type(Chemical* chemical) { m_ocean = chemical; }

	Chemical* Planet::get_ocean_type() const { return m_ocean; }

	void Planet::add_to_atmosphere(Chemical* chemical, Gigamoles amount) { m_atmosphere.push_back({chemical, amount}); }
}
