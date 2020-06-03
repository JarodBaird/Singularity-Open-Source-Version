#include "MainMenu.h"

#include "Singularity.Data/Game.h"
#include "TestScreens/ColorTest.h"
#include "../../GalaxyGeneration/GalaxySettings.h"
#include "Altair.Engine/FileSystem/DirectoryIterator.h"
#include "Play/SelectGalaxy.h"
#include "Credits/Credits.h"
#include "TestScreens/SpriteLoadTest.h"

namespace Singularity
{
	MainMenu::MainMenu()
	{
		m_title = "Singularity";

		const Altair::DirectoryIterator iterator("GameData\\Saves");
		const bool save_files_present = iterator.get_subdirectory_count() > 0;

		m_menu_items.push_back(std::make_unique<MenuItem>("Play", "Begin a new game or load a saved game.",
		                                                  [](Game* game)
		                                                  {
			                                                  game->push_state(new SelectGalaxyScreen());
		                                                  }, !save_files_present));

		m_menu_items.push_back(std::make_unique<MenuItem>("Create a new Galaxy",
		                                                  "Create a new galaxy to start games from.", [](Game* game)
		                                                  {
			                                                  game->push_state(new GalaxySettings());
		                                                  }));

		m_menu_items.push_back(std::make_unique<MenuItem>("Test Colors", "See how your color scheme looks.",
		                                                  [](Game* game) { game->push_state(new ColorTest()); }));

		m_menu_items.push_back(std::make_unique<MenuItem>("Sprite Load Test",
		                                                  "Loads a large number of sprites onto the screen.",
		                                                  [](Game* game) { game->push_state(new SpriteLoadTest()); }));

		m_menu_items.push_back(std::make_unique<MenuItem>("Credits", "See how your color scheme looks.", [](Game* game)
		{
			game->push_state(new Credits());
		}));

		m_menu_items.push_back(std::make_unique<MenuItem>("Exit Program", "Exit the program.", [](Game* game)
		{
			game->quit();
		}));
	}

	void MainMenu::update(Game*) {}

	void MainMenu::draw(Game* game) { this->print_menu_items(game); }
}
