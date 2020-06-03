#include "SpeciesFactory.h"
#include "Altair.Engine/Util/Random.h"

namespace Singularity
{
	SpeciesFactory::SpeciesFactory() = default;

	Species* SpeciesFactory::create(Species::Type type, Chemical* solvent)
	{
		Species* s = new Species("", "", "", type, solvent, nullptr);
		return s;
	}
}
