#ifndef __FOREST_H
#define __FOREST_H
#include "../TerrainFeature.h"
#include "../../../Life/Species.h"

namespace Singularity
{
	class Forest final : public TerrainFeature
	{
	private:
		Species* m_species;
	public:
		Forest(CelestialBody* parent_body);
		Forest(CelestialBody* parent_body, Species* species);
		void update() override;
	};
}
#endif // !__FOREST_H
