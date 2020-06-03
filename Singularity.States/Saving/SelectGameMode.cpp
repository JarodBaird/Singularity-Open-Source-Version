#include "SelectGameMode.h"
#include "Singularity.States/Modes/Lore/LoreScreen.h"
#include "SelectCivilization.h"

namespace Singularity
{
	SelectGameMode::SelectGameMode()
	{
		m_title = "Select a Game Mode";

		m_menu_items.push_back(std::make_unique<MenuItem>("Singularity Mode", [](Game* game)
		{
			game->push_state(new SelectCivilization());
		}));

		m_menu_items.push_back(std::make_unique<MenuItem>("Lore Mode", [](Game* game)
		{
			game->push_state(new LoreScreen());
		}));

		m_menu_items.push_back(std::make_unique<MenuItem>("Cancel", [](Game* game) { game->pop_state(); }));
	}

	void SelectGameMode::update(Game*) { }

	void SelectGameMode::draw(Game* game) { this->print_menu_items(game); }
}
