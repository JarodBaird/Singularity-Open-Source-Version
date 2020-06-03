#ifndef __MEDIUM_TERRAIN_MAP_H
#define __MEDIUM_TERRAIN_MAP_H
#include <utility>

#include "../TerrainMap.h"

namespace Singularity
{
	class MediumTerrainMap final : public TerrainMap
	{
	public:
		MediumTerrainMap() : TerrainMap(64, "Medium") {}
		MediumTerrainMap(std::string map) : TerrainMap(64, "Medium", std::move(map)) {}
	};
}
#endif // !__MEDIUM_TERRAIN_MAP_H
