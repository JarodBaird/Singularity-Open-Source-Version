#ifndef POPULATION_H
#define POPULATION_H

namespace Singularity
{
	class Population
	{
	private:
		unsigned long long m_population;
	public:
		Population();
		Population(unsigned long long starting_population);
		void update();
		unsigned long long get_population() const;
	};
}
#endif // !POPULATION_H
