#ifndef __MAIN_MENU_H
#define __MAIN_MENU_H
#include "../../BaseStates/Menu/Menu.h"

namespace Singularity
{
	class MainMenu final : public Menu
	{
	public:
		MainMenu();
		void update(Game* game) override;
		void draw(Game* game) override;
	};
}
#endif // !__MAIN_MENU_H
