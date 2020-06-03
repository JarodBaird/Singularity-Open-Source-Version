#ifndef  __REFINERY_H
#define __REFINERY_H
#include "Structure.h"

namespace Singularity
{
	class Refinery final : public Structure
	{
	public:
		Refinery(CelestialBody* parent_body, Civilization* owner);
		std::vector<std::string> get_description() override;
		void update() override;
	};
}
#endif // !__REFINERY_H
