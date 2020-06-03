#ifndef __UNIVERSAL_VARIABLES_H
#define __UNIVERSAL_VARIABLES_H

namespace Singularity
{
	struct UniversalVariables
	{
	public:
		static int screen_width;
		static int screen_height;

		static int sprite_width;
		static int sprite_height;

		static int tile_size;

		static bool fullscreen;

		//Sound
		static int music_volume;

		static bool show_fps;

		static int get_max_x();
		static int get_max_y();
	};
}
#endif // !__UNIVERSAL_VARIABLES_H
