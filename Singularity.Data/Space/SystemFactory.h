#ifndef __SYSTEM_FACTORY_H
#define __SYSTEM_FACTORY_H
#include "StarchartObject.h"
#include <vector>
#include "Altair.Engine/Util/Random.h"
#include "../Physics/Chemistry/Element.h"
#include "../Physics/Chemistry/Compound.h"
#include "Bodies/Planets/PlanetFactory.h"

namespace Singularity
{
	class SystemFactory
	{
	private:
		Altair::Random m_random;
		PlanetFactory m_planet_factory;
		std::vector<Element*> m_elements;
		std::vector<Compound*> m_compounds;
		std::vector<Element*> elements;
		std::vector<Compound*> compounds;
	public:
		SystemFactory(std::vector<Element*> elements, std::vector<Compound*> compounds);

		StarchartObject* create(const std::string& name, int x, int y);
		StarchartObject* create_star(const std::string& name, int x, int y);
		StarchartObject* create_blackhole(std::string name, int x, int y) const;
		StarchartObject* create_dyson_sphere(std::string name, int x, int y) const;
		StarchartObject* create_rogue_planet(const std::string& name, int x, int y);
	};
}
#endif // !__SYSTEM_FACTORY_H
