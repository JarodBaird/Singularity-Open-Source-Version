#ifndef __COMMS_SCREEN_H
#define __COMMS_SCREEN_H
#include "Singularity.States/BaseStates/Menu/Menu.h"

namespace Singularity
{
	class CommsScreen final : public Menu
	{
	public:
		CommsScreen(Game* game);
		void update(Game* game) override;
		void draw(Game* game) override;
	};
}
#endif // !__COMMS_SCREEN_H
