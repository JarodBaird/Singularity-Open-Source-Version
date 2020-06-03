#ifndef __FIGURE_H
#define __FIGURE_H
#include "Species.h"
#include "../Civilization/Civilization.h"

namespace Singularity
{
	class Figure
	{
	protected:
		Species* m_species;
		Civilization* m_nationality;
	public:
		Figure();
		Species* get_species() const;
		Civilization* get_nationality() const;
	};
}
#endif // !__FIGURE_H
