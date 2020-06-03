#include "Generator.h"
#include "../../../Civilization/Civilization.h"

namespace Singularity
{
	Generator::Generator(CelestialBody* parent_body, Civilization* owner) : Structure(parent_body, owner)
	{
		m_sprite = 0xec;
		m_color = Altair::Color::orange;
		m_name = "Generator";
	}

	void Generator::update()
	{
		if (is_built()) { m_owner->update_energy(1); }
		else { m_build_progress += 0.1; }
	}

	std::vector<std::string> Generator::get_description()
	{
		return std::vector<std::string>{

		};
	}
}
