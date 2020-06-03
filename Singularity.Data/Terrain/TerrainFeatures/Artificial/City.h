#ifndef __CITY_H
#define __CITY_H
#include "Structure.h"

namespace Singularity
{
	class City final : public Structure
	{
	private:
		unsigned long int m_population;
	public:
		City(CelestialBody* parent_body, Civilization* owner);
		void update() override;
	};
}
#endif // !__CITY_H
