#ifndef __STAR_H
#define __STAR_H

#include "../CelestialBody.h"

namespace Singularity
{
	class Star final : public CelestialBody
	{
	public:
		Star(Altair::Color c);
	};
}
#endif // !__STAR_H
