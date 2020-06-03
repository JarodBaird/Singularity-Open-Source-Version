#include "Gigamole.h"

namespace Singularity
{
	Gigamoles operator ""_mol(uint64_t n) { return Gigamoles{n / 1000UL}; }

	Gigamoles operator ""_Gmol(uint64_t n) { return Gigamoles{n}; }
}
