#include "Population.h"
#include <cmath>

namespace Singularity
{
	Population::Population() { m_population = 0; }

	Population::Population(unsigned long long starting_population) { m_population = starting_population; }

	void Population::update()
	{
		const unsigned long long fifty_billion = 50 * static_cast<unsigned long long>(1000000000);
		if (m_population >= fifty_billion) { m_population = fifty_billion; }
		else
		{
			double const rate = .1 / (128 * 32 * 16);
			m_population = static_cast<unsigned long long>(static_cast<double>(m_population) * pow(M_E, rate));
		}
	}

	unsigned long long Population::get_population() const { return m_population; }
}
