#ifndef __SPECIES_FACTORY_H
#define __SPECIES_FACTORY_H
#include "Species.h"

namespace Singularity
{
	class SpeciesFactory
	{
	public:
		SpeciesFactory();
		static Species* create(Species::Type type, Chemical* solvent);
	};
}
#endif // !__SPECIES_FACTORY_H
