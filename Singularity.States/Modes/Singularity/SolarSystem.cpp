#include "SolarSystem.h"
#include "PlanetTerrain.h"
#include "Singularity.Data/Game.h"
#include "Singularity.Data/Settings/UniversalVariables.h"

namespace Singularity
{
	SolarSystem::SolarSystem(StarchartObject* current_system)
	{
		m_paused = false;
		m_current_system = current_system;
		std::vector<CelestialBody*> children = m_current_system->get_children();
		for (CelestialBody* child : children)
		{
			m_menu_items.push_back(std::make_unique<MenuItem>(child->get_name(), [=](Game* game)
			{
				std::vector<CelestialBody*> system_children = current_system->get_children();
				CelestialBody* selected_child = system_children.at(m_selected_item);
				if (selected_child->get_can_visit())
				{
					game->pop_all_states();
					game->push_state(new PlanetTerrain(selected_child));
				}
			}));
		}
	}

	void SolarSystem::update(Game*) { }

	void SolarSystem::draw(Game* game)
	{
		const int screen_width = UniversalVariables::get_max_x() - 20;

		const int mid_x = screen_width / 2;
		const int mid_y = UniversalVariables::get_max_y() / 2;

		std::vector<CelestialBody*> children = m_current_system->get_children();
		unsigned long long total_pop = 0;
		for (CelestialBody* child : children)
		{
			game->draw(child->to_sprite(mid_x + child->get_x(), mid_y + child->get_y()));
			total_pop += child->get_total_population();
		}

		CelestialBody* parent = m_current_system->get_parent();
		game->draw(parent->to_sprite(mid_x, mid_y));

		game->draw(Altair::TextItem(screen_width, 1, std::to_string(total_pop), Altair::Color::white));

		this->print_menu_items(game, screen_width, 2);
	}
}
