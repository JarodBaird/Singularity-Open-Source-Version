#include "Structure.h"

namespace Singularity
{
	Structure::Structure(CelestialBody* parent_body, Civilization* owner) : TerrainFeature(parent_body)
	{
		m_owner = owner;
		m_build_progress = 0;
	}

	bool Structure::is_built() const { return m_build_progress > 100; }

	Altair::Color Structure::get_color()
	{
		if (is_built()) { return m_color; }
		return Altair::Color::orange;
	}

	unsigned char Structure::get_sprite()
	{
		if (is_built()) { return m_sprite; }
		return 0x2d;
	}
}
