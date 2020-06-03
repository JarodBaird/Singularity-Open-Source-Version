#include "Refinery.h"

#include "../../../Civilization/Civilization.h"

namespace Singularity
{
	Refinery::Refinery(CelestialBody* parent_body, Civilization* owner) : Structure(parent_body, owner)
	{
		m_sprite = 0x15;
		m_color = Altair::Color::blue;
		m_name = "Refinery";
	}

	std::vector<std::string> Refinery::get_description()
	{
		std::vector<std::string> description;
		for (Entity* inventory : m_inventory)
		{
			description.push_back(inventory->get_name() + "(" + std::to_string(inventory->get_size()) + ")");
		}
		return description;
	}

	void Refinery::update()
	{
		if (is_built())
		{
			for (Entity* entity : m_inventory)
			{
				if (entity->has_tag("Ore"))
				{
					remove_inventory(entity);
					Entity* refined = new Item("Refined", entity->get_size(), std::vector<std::string>{});

					for (Entity* mergable_entity : m_inventory)
					{
						if (mergable_entity->can_merge(refined))
						{
							mergable_entity->merge(refined);
							return;
						}
					}
					m_inventory.push_back(refined);

					delete entity;

					return;
				}
			}

			// If nothing was refined. 
			std::vector<std::shared_ptr<TerrainFeature>> structures = m_parent_body->get_structures();
			for (const std::shared_ptr<TerrainFeature>& structure : structures)
			{
				if (structure->get_name() != "Refinery")
				{
					std::vector<Entity*> inventory = structure->get_inventory();
					for (Entity* entity : inventory)
					{
						if (entity->has_tag("Ore"))
						{
							entity = structure->remove_inventory(entity);
							m_inventory.push_back(entity);
							return;
						}
					}
				}
			}
		}
		else { m_build_progress += 0.1; }
	}
}
