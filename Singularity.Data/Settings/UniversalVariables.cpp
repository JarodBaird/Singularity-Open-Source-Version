#include "UniversalVariables.h"

namespace Singularity
{
	int UniversalVariables::screen_width = 800;
	int UniversalVariables::screen_height = 600;

	int UniversalVariables::sprite_width = 16;
	int UniversalVariables::sprite_height = 16;

	int UniversalVariables::tile_size = 32;

	bool UniversalVariables::fullscreen = false;

	int UniversalVariables::music_volume = 100;

	bool UniversalVariables::show_fps = false;

	int UniversalVariables::get_max_x() { return screen_width / tile_size; }

	int UniversalVariables::get_max_y() { return screen_height / tile_size; }
}
