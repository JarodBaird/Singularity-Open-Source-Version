#ifndef __SELECT_CIVILIZATION_H
#define __SELECT_CIVILIZATION_H
#include <vector>

#include "../BaseStates/Menu/Menu.h"

namespace Singularity
{
	class SelectCivilization final : public Menu
	{
	private:
		bool m_menu_items_generated;
		std::vector<CelestialBody*> m_candidates;
	public:
		SelectCivilization();
		void update(Game* game) override;
		void draw(Game* game) override;
	};
}
#endif // __SELECT_CIVILIZATION_H
