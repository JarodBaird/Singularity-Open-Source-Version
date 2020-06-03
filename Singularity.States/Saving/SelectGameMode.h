#ifndef __SELECT_GAME_MODE_H
#define __SELECT_GAME_MODE_H
#include "../BaseStates/Menu/Menu.h"

namespace Singularity
{
	class SelectGameMode final : public Menu
	{
	public:
		SelectGameMode();
		void update(Game* game) override;
		void draw(Game* game) override;
	};
}
#endif // !__SELECT_GAME_MODE_H
