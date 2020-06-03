#ifndef PLANET_H
#define PLANET_H
#include "../CelestialBody.h"
#include "../../../Physics/Chemistry/Compound.h"

namespace Singularity
{
	struct Gigamoles;

	class Planet final : public CelestialBody
	{
	private:
		Chemical* m_ocean;
	public:
		Planet(std::string name, OrbitData orbit, std::unique_ptr<TerrainMap> terrain);

		void add_to_atmosphere(Chemical* chemical, Gigamoles amount);
		void set_ocean_type(Chemical* chemical);
		Chemical* get_ocean_type() const;
	};
}
#endif // !PLANET_H
