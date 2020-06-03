#ifndef __GENERATOR_H
#define __GENERATOR_H
#include "Structure.h"

namespace Singularity
{
	class Generator final : public Structure
	{
	public:
		Generator(CelestialBody* parent_body, Civilization* owner);
		void update() override;
		std::vector<std::string> get_description() override;
	};
}
#endif // !__GENERATOR_H
