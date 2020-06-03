#ifndef SMALL_TERRAIN_MAP_H
#define SMALL_TERRAIN_MAP_H
#include <utility>

#include "../TerrainMap.h"

namespace Singularity
{
	class SmallTerrainMap final : public TerrainMap
	{
	public:
		SmallTerrainMap() : TerrainMap(32, "Small") {}
		SmallTerrainMap(std::string map) : TerrainMap(32, "Small", std::move(map)) {}
	};
}
#endif // !SMALL_TERRAIN_MAP_H
