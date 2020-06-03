#include "Forest.h"
#include "Altair.Engine/Graphics/Sprite.h"

namespace Singularity
{
	Forest::Forest(CelestialBody* parent_body) : TerrainFeature(parent_body)
	{
		m_species = nullptr;
		m_sprite = 0x05;
		m_color = Altair::Color::green;
		m_name = "Forest";
	}

	Forest::Forest(CelestialBody* parent_body, Species* species) : TerrainFeature(parent_body)
	{
		m_species = species;
		m_sprite = 0x05;
		m_color = Altair::Color::green;
		m_name = m_species->get_common_name() + " Forest";
	}

	void Forest::update() { }
}
