#ifndef TINY_TERRAIN_MAP_H
#define	TINY_TERRAIN_MAP_H
#include <utility>


#include "../TerrainMap.h"

namespace Singularity
{
	class TinyTerrainMap final : public TerrainMap
	{
	public:
		TinyTerrainMap() : TerrainMap(16, "Tiny") {}
		TinyTerrainMap(std::string map) : TerrainMap(16, "Tiny", std::move(map)) {}
	};
}
#endif // !TINY_TERRAIN_MAP_H
