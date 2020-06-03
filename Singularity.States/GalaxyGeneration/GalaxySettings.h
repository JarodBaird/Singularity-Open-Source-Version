#ifndef __GALAXY_SETTINGS_SCREEN_H
#define __GALAXY_SETTINGS_SCREEN_H
#include "../BaseStates/Menu/Menu.h"

namespace Singularity
{
	class GalaxySettings final : public Menu
	{
	public:
		GalaxySettings();
		void update(Game* game) override;
		void draw(Game* game) override;
	};
}
#endif // !__GALAXY_SETTINGS_SCREEN_H
