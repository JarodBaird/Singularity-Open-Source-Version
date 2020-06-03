#ifndef __ASTEROID_BELT_H
#define __ASTEROID_BELT_H
#include "../CelestialBody.h"

namespace Singularity
{
	class AsteroidBelt final : public CelestialBody
	{
	private:
		short m_width;
	public:
		AsteroidBelt();
	};
}
#endif // !__ASTEROID_BELT_H
