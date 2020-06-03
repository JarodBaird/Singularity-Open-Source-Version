#include "GasPlanet.h"

#include "Altair.Engine/Graphics/Color.h"

namespace Singularity
{
	GasPlanet::GasPlanet(std::string name, OrbitData orbit)
	{
		m_sprite_x = 14;
		m_sprite_y = 14;

		Altair::Color possible_colors[] = {
			Altair::Color::red,
			Altair::Color::maroon,
			Altair::Color::orange,
			Altair::Color::brown,
			Altair::Color::yellow,
			Altair::Color::olive,
			Altair::Color::lime,
			Altair::Color::green,
			Altair::Color::aqua,
			Altair::Color::teal,
			Altair::Color::blue,
			Altair::Color::navy,
			Altair::Color::fuchsia,
			Altair::Color::purple,
			Altair::Color::white,
			Altair::Color::silver,
		};
		m_land_color = possible_colors[rand() % 16];

		m_name = std::move(name);
		m_orbit = orbit;
		m_terrain_map = nullptr;
	}
}
