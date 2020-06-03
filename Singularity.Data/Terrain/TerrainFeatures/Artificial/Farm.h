#ifndef __FARM_H
#define __FARM_H
#include "Structure.h"

namespace Singularity
{
	class Farm final : public Structure
	{
	public:
		Farm(CelestialBody* parent_body, Civilization* owner);
		void update() override;
	};
}
#endif // !__FARM_H
