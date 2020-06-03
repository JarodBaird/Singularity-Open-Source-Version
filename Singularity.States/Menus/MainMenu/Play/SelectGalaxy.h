#ifndef __SELECT_GALAXY_H
#define __SELECT_GALAXY_H
#include "../../../BaseStates/Menu/Menu.h"

namespace Singularity
{
	class SelectGalaxyScreen final : public Menu
	{
	public:
		SelectGalaxyScreen();

		void update(Game* game) override;
		void draw(Game* game) override;
	};
}
#endif // !__SELECT_GALAXY_H
