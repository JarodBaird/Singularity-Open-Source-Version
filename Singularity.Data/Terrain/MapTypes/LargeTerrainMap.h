#ifndef LARGE_TERRAIN_MAP_H
#define LARGE_TERRAIN_MAP_H
#include <utility>

#include "../TerrainMap.h"

namespace Singularity
{
	class LargeTerrainMap final : public TerrainMap
	{
	public:
		LargeTerrainMap() : TerrainMap(128, "Large") {}
		LargeTerrainMap(std::string map) : TerrainMap(128, "Large", std::move(map)) {}
	};
}
#endif // !LARGE_TERRAIN_MAP_H
