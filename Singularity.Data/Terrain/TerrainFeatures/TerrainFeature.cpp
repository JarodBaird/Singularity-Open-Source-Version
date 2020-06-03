#include "TerrainFeature.h"

#include "../../Space/Bodies/CelestialBody.h"

namespace Singularity
{
	TerrainFeature::TerrainFeature(CelestialBody* celestial_body)
	{
		m_parent_body = celestial_body;
		m_sprite = 0x00;
		m_storage_capacity = 0;
	}

	Altair::Color TerrainFeature::get_color() { return m_color; }

	unsigned char TerrainFeature::get_sprite() { return m_sprite; }

	std::string TerrainFeature::get_name() const { return m_name; }

	std::vector<Entity*> TerrainFeature::get_inventory() const { return m_inventory; }

	Entity* TerrainFeature::remove_inventory(Entity* entity)
	{
		m_inventory.erase(std::remove(m_inventory.begin(), m_inventory.end(), entity), m_inventory.end());
		return entity;
	}

	std::vector<std::string> TerrainFeature::get_description() { return std::vector<std::string>{}; }
}
