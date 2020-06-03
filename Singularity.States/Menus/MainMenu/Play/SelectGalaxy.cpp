#include "SelectGalaxy.h"
#include "../../../Saving/LoadingGalaxy.h"
#include "Altair.Engine/FileSystem/DirectoryIterator.h"

namespace Singularity
{
	SelectGalaxyScreen::SelectGalaxyScreen()
	{
		m_title = "Select a Galaxy";
		const Altair::DirectoryIterator iter = Altair::DirectoryIterator("GameData\\Saves");

		for (const std::string& galaxy_name : iter.get_subdirectories())
		{
			m_menu_items.push_back(std::make_unique<MenuItem>(galaxy_name, [=](Game* game)
			{
				game->push_state(
					new LoadingGalaxy(get_selected_value()));
			}));
		}
	}

	void SelectGalaxyScreen::update(Game*) { }

	void SelectGalaxyScreen::draw(Game* game) { this->print_menu_items(game); }
}
