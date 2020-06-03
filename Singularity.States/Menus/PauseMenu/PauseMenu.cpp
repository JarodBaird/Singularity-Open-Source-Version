#include "PauseMenu.h"
#include "../../Saving/SavingGalaxy.h"

namespace Singularity
{
	PauseMenu::PauseMenu()
	{
		m_paused = true;
		m_menu_loaded = false;

		m_title = "Paused";

		m_menu_items.push_back(std::make_unique<MenuItem>("Resume", [](Game* game) { game->pop_state(); }));
	}

	void PauseMenu::update(Game* game)
	{
		if (!m_menu_loaded)
		{
			if (!game->model->starchart.empty())
			{
				m_menu_items.push_back(std::make_unique<MenuItem>("Save and Quit", [](Game* game)
				{
					game->pop_all_states();
					game->push_state(new SavingGalaxy(game->model->galaxy_name));
				}));
			}
			m_menu_loaded = true;
		}
	}

	void PauseMenu::draw(Game* game) { this->print_menu_items(game); }
}
