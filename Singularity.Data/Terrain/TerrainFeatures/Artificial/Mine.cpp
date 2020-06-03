#include "Mine.h"

#include "../../../Space/Bodies/CelestialBody.h"

namespace Singularity
{
	Mine::Mine(CelestialBody* parent_body, Civilization* owner) : Structure(parent_body, owner)
	{
		m_sprite = 0x9e;
		m_color = Altair::Color::brown;
		m_name = "Mine";
	}

	void Mine::update()
	{
		if (is_built())
		{
			Item* ore = CelestialBody::mine();
			for (Entity* inventory : m_inventory)
			{
				if (inventory->can_merge(ore))
				{
					inventory->merge(ore);
					return;
				}
			}
			m_inventory.push_back(ore);
		}
		else { m_build_progress += 0.1; }
	}

	std::vector<std::string> Mine::get_description()
	{
		std::vector<std::string> description;
		for (Entity* inventory : m_inventory)
		{
			description.push_back(inventory->get_name() + "(" + std::to_string(inventory->get_size()) + ")");
		}
		return description;
	}
}
