#ifndef GAS_PLANET_H
#define GAS_PLANET_H
#include "../CelestialBody.h"

namespace Singularity
{
	class GasPlanet final : public CelestialBody
	{
	public:
		GasPlanet(std::string name, OrbitData orbit);
	};
}
#endif // !GAS_PLANET_H
