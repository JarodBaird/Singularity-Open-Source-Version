#ifndef __SOLAR_SYSTEM_SCREEN_H
#define __SOLAR_SYSTEM_SCREEN_H
#include "Singularity.Data/Space/StarchartObject.h"
#include "Singularity.States/BaseStates/Menu/Menu.h"

namespace Singularity
{
	class SolarSystem final : public Menu
	{
	private:
		StarchartObject* m_current_system;
	public:
		SolarSystem(StarchartObject* current_system);
		void update(Game* game) override;
		void draw(Game* game) override;
	};
}
#endif // !__SOLAR_SYSTEM_SCREEN_H
