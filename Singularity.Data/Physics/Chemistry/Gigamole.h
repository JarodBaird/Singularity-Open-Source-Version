#ifndef __GIGAMOLE_H
#define __GIGAMOLE_H

#include <cstdint>

namespace Singularity
{
	struct Gigamoles
	{
	public:
		uint64_t value;
	};

	Gigamoles operator ""_mol(uint64_t n);

	Gigamoles operator ""_Gmol(uint64_t n);
}
#endif // !__GIGAMOLE_H
