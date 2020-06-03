#ifndef TERRAIN_MAP_H
#define TERRAIN_MAP_H
#include <utility>

#include "TerrainFeatures/TerrainFeature.h"
#include "../../Altair.Engine/FileSystem/FileReaders/FileReader.h"

namespace Singularity
{
	class TerrainMap : public Altair::Serializable
	{
	protected:
		struct TerrainTile
		{
		public:
			TerrainTile();

			std::shared_ptr<TerrainFeature> structure;
			uint8_t land_height;
			uint8_t ocean_depth;
		};

		uint32_t m_width;
		uint32_t m_height;
		std::vector<TerrainTile> m_map;
		std::string m_map_type;
		uint32_t to_index(uint32_t x, uint32_t y) const;
		uint32_t get_number_of_tiles() const;
	public:
		TerrainMap(uint32_t height, std::string map_type) : TerrainMap(height, std::move(map_type), "") {}
		TerrainMap(uint32_t height, std::string map_type, std::string map);
		virtual ~TerrainMap() = default;
		TerrainMap(const TerrainMap&) = default;
		TerrainMap(TerrainMap&&) = default;
		TerrainMap& operator =(const TerrainMap&) = default;
		TerrainMap& operator =(TerrainMap&&) = default;

		uint32_t get_map_width() const;
		uint32_t get_map_height() const;
		std::string get_map_type() const;

		uint8_t get_terrain_height(uint32_t x, uint32_t y);
		void set_terrain_height(uint32_t x, uint32_t y, uint8_t height);

		uint8_t get_ocean_depth(uint32_t x, uint32_t y);
		void set_ocean_depth(uint32_t x, uint32_t y, uint8_t depth);

		uint16_t get_total_height(uint32_t x, uint32_t y);

		std::shared_ptr<TerrainFeature> get_structure(uint32_t x, uint32_t y);
		void set_structure(uint32_t x, uint32_t y, std::shared_ptr<TerrainFeature> structure);

		void erode();
		bool erode(uint32_t x, uint32_t y);

		std::string serialize() override;
	};
}
#endif // !TERRAIN_MAP_H
