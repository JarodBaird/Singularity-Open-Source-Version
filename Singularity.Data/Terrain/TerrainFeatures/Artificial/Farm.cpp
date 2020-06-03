#include "Farm.h"
#include "../../../Civilization/Civilization.h"

namespace Singularity
{
	Farm::Farm(CelestialBody* parent_body, Civilization* owner) : Structure(parent_body, owner)
	{
		m_sprite = 0x3d;
		m_color = Altair::Color::lime;
		m_name = "Farm";
	}

	void Farm::update()
	{
		if (is_built()) { m_owner->update_food(1); }
		else { m_build_progress += 0.1; }
	}
}
