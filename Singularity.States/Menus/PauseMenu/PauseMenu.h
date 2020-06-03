#ifndef __PAUSE_MENU_H
#define __PAUSE_MENU_H
#include "../../BaseStates/Menu/Menu.h"

namespace Singularity
{
	class PauseMenu final : public Menu
	{
	private:
		bool m_menu_loaded;
	public:
		PauseMenu();
		void update(Game* game) override;
		void draw(Game* game) override;
	};
}
#endif // !__PAUSE_MENU_H
