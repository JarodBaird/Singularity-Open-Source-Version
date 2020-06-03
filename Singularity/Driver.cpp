#include "Altair.Engine/Graphics/Window.h"
#include "Singularity.Data/Game.h"
#include "Altair.Engine/FileSystem/FileReaders/SettingsReader.h"
#include "Singularity.Data/Settings/UniversalVariables.h"
#include "Singularity.States/Menus/MainMenu/MainMenu.h"
#include "Singularity.States/Menus/PauseMenu/PauseMenu.h"

void initialize_settings()
{
	Altair::SettingsReader settings_reader = Altair::SettingsReader("Init.cfg");
	Singularity::UniversalVariables::screen_width = settings_reader.get_int("WindowX");
	Singularity::UniversalVariables::screen_height = settings_reader.get_int("WindowY");
	Singularity::UniversalVariables::music_volume = settings_reader.get_int("MusicVolume");
	Singularity::UniversalVariables::tile_size = settings_reader.get_int("TileSize");
	Singularity::UniversalVariables::fullscreen = settings_reader.get_bool("Fullscreen");
	Singularity::UniversalVariables::show_fps = settings_reader.get_bool("ShowFPS");
}

void begin()
{
	initialize_settings();

	std::unique_ptr<Altair::Window> window = std::make_unique<Altair::Window>(
		Singularity::UniversalVariables::screen_width, Singularity::UniversalVariables::screen_height,
		Singularity::UniversalVariables::fullscreen);

	std::unique_ptr<Singularity::Game> game = std::make_unique<Singularity::Game>(
		new Singularity::MainMenu(), new Singularity::PauseMenu(), std::move(window));

	game->begin();
}

int main()
{
	begin();

	return 0;
}
