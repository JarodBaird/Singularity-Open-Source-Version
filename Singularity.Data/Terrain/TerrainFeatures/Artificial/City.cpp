#include "City.h"
#include <cmath>

namespace Singularity
{
	City::City(CelestialBody* parent_body, Civilization* owner) : Structure(parent_body, owner)
	{
		m_color = Altair::Color::yellow;
		m_sprite = 0xea;
		m_population = 100000;
		m_name = "City";
	}

	void City::update()
	{
		if (is_built())
		{
			const double birth_rate = 0.000005;

			if (m_population < 1000000) { m_population = m_population * static_cast<unsigned>(pow(M_E, birth_rate)); }
			else { m_population = 1000000; }
		}
		else { m_build_progress += 0.01; }
	}
}
