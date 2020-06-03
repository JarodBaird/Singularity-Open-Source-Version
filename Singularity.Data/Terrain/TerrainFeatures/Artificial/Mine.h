#ifndef __MINE_H
#define __MINE_H
#include "Structure.h"

namespace Singularity
{
	class Mine final : public Structure
	{
	public:
		Mine(CelestialBody* parent_body, Civilization* owner);
		void update() override;
		std::vector<std::string> get_description() override;
	};
}
#endif // !__MINE_H
