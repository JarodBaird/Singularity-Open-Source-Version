#ifndef __PLANET_FACTORY_H
#define __PLANET_FACTORY_H
#include "Planet.h"
#include "GasPlanet.h"
#include "Altair.Engine/Util/Random.h"

#include "Singularity.Data/Physics/Chemistry/Gigamole.h"

namespace Singularity
{
	class PlanetFactory
	{
	private:
		std::vector<Element*> m_elements;
		std::vector<Compound*> m_compounds;
		std::vector<Chemical*> m_atmosphere_candidates;
		std::vector<Chemical*> m_ocean_candidates;

		Altair::Random m_random;

		Gigamoles generate_crust_amount(int atomic_number) const;
		static Gigamoles generate_atmosphere_amount();
		static Gigamoles generate_ocean_amount();
	public:
		PlanetFactory(const std::vector<Element*>& elements, const std::vector<Compound*>& compounds);
		Planet* create_terrestrial(std::string name);
		GasPlanet* create_gas(std::string name) const;
	};
}
#endif // !__PLANET_FACTORY_H
