#ifndef __LORE_SCREEN_H
#define __LORE_SCREEN_H
#include "Singularity.States/BaseStates/Menu/Menu.h"

namespace Singularity
{
	class LoreScreen final : public Menu
	{
	public:
		LoreScreen();
		void update(Game* game) override;
		void draw(Game* game) override;
	};
}
#endif // !__LORE_SCREEN_H
