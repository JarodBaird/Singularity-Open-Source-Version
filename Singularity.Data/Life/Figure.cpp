#include "Figure.h"

namespace Singularity
{
	Figure::Figure()
	{
		m_species = nullptr;
		m_nationality = nullptr;
	}

	Species* Figure::get_species() const { return m_species; }

	Civilization* Figure::get_nationality() const { return m_nationality; }
}
